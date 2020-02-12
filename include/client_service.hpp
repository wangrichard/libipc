#ifndef __CLIENT_SERVICE__
#define __CLIENT_SERVICE__

#include <iostream>
#include <string>

#include <json-c/json.h>


#define BUF_SIZE (1024)


namespace ipc
{

class client_service
{
public:
	client_service() = delete;
	client_service(void (*client_cb)(json_object *json));
	~client_service();
	int client_send(const char * to_path, json_object *json);
	void (*client_cb)(json_object *json); 

	bool m_shutdown = false;

private:
	json_object *m_json = nullptr;
};

}

#endif //__CLIENT_SERVICE__
