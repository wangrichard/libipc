#ifndef __SERVER_SERVICE__
#define __SERVER_SERVICE__

#include <iostream>
#include <string>
#include <thread>

#include <json-c/json.h>


#define BUF_SIZE (1024)


namespace ipc
{
class server_service
{
public:
	server_service() = delete;
	server_service(const std::string & path, void (*server_cb)(json_object *json));
	~server_service();
	int start(void);
	void (*server_cb)(json_object *json);
	
	bool m_shutdown = false;
	int listen_fd;
	json_object *m_json = nullptr;

private:
	std::string m_path;
	std::thread m_thread;
};

}

#endif //__SERVER_SERVICE__