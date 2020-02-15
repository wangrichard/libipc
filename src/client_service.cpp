#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "client_service.hpp"


namespace ipc
{

client_service::client_service(void (*client_cb)(json_object *json))
:client_cb(client_cb)
{
}


client_service::~client_service()
{
	m_shutdown = true;
}


int client_service::client_send(const char * to_path, json_object *json)
{
    int fd;
    struct sockaddr_un un;
    const char *jp;
	char buf[BUF_SIZE];
	std::string a_to_path, tmp_str;
	struct timeval timeout;

	if ((to_path==nullptr) || (json==nullptr))
	{
	 	std::cout << "Input parameter null." << std::endl;
		return -1;
	}

	tmp_str = to_path;
	a_to_path = "/tmp/socket." + tmp_str;

	if ((jp=json_object_to_json_string(json)) == nullptr)
	{
		perror("json_object_to_json_string error");
		return -1;
	}
		
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        return -1;
    }

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
	setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));

    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strncpy(un.sun_path, a_to_path.c_str(), sizeof(un.sun_path) - 1);

    if (connect(fd, (struct sockaddr *) &un, sizeof(un)) < 0)
    {
        perror("connect error");
        return -1;
    }

	if (write(fd, jp, strlen(jp)+1) < 0)
	{
	    perror("write error");
	    return -1;
	}

    if (read(fd, buf, sizeof(buf)) > 0) 
    {
        //printf("%s\n", buf);
        if (m_json != nullptr)
        {
        	json_object_put(m_json);	
        }
        m_json = json_tokener_parse(buf);
		if (m_json != nullptr)
		{
			client_cb(m_json);
		}
	}
	else
	{
		perror("read error");
		return -1;	
	}
		
    return 0;
}

} // ipc
