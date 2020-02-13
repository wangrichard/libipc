#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "server_service.hpp"

#define QLEN (8)

namespace ipc
{

void server_proc(server_service *s)
{
	int fd=0, n;
  const char *jp;
	char buf[BUF_SIZE];

	if (s == nullptr)
	{
		printf("Input parameter null.\n");
		return;
	}

    while (!s->m_shutdown)
    {
        if ((fd = accept(s->listen_fd, NULL, NULL)) == -1)
        {
            perror("accpet error");
            continue;
        }

        if ((n = read(fd, buf, sizeof(buf))) > 0) 
        {
            //printf("%s\n", buf);

            if (s->m_json != nullptr)
            {
            	json_object_put(s->m_json);	
            }
            s->m_json = json_tokener_parse(buf);
            if (s->m_json != nullptr)
            {
            	s->server_cb(s->m_json);
				if ((jp=json_object_to_json_string(s->m_json)) != nullptr)
				{	
					if (write(fd, jp, strlen(jp)+1) < 0)
					{
					    perror("write error");
					    continue;
					}
				}
            }
        }
        else
        {
        	perror("read error");
        	continue;	
        }
    }
    
    if (fd > 0)
    {
    	close(fd);
    }
}


server_service::server_service(const std::string & path,
								void (*server_cb)(json_object *json))
:server_cb(server_cb),
m_path("/tmp/socket." + path)
{
}

server_service::~server_service()
{
	if (m_json != NULL)
	{
		json_object_put(m_json);
		m_json = nullptr;
	}	

	close(listen_fd);

	m_shutdown = true;
	if (m_thread.joinable())
	{
		m_thread.join();
	}
}


int server_service::start(void)
{
   struct sockaddr_un un;

    if ((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        return -1;
    }

    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strncpy(un.sun_path, m_path.c_str(), sizeof(un.sun_path) - 1);
	unlink(m_path.c_str());
	
    if (bind(listen_fd, (struct sockaddr *) &un, sizeof(un)) < 0) {
        perror("bind error");
        return -1;
    }

    printf("UNIX Domain Socket bound\n");

    if (listen(listen_fd, QLEN) < 0) {
        perror("listen error");
        return -1;
    }
    m_thread = std::thread(server_proc, this);
    
    return 0;
}

}
