#include <unistd.h>

#include "server_service.hpp"

void server_cb(json_object *json)
{
	json_object *jstatus;
	
	if (json == nullptr)
	{
		printf("Input parameter null\n");
		return;	
	}
	
	printf("server cb\n");
	
	if (nullptr != (jstatus=json_object_object_get(json, "status")))
	{
		printf("status: %d\n", json_object_get_int(jstatus));
	}
	if (nullptr != (jstatus=json_object_object_get(json, "operation")))
	{
		printf("operation: %s\n", json_object_get_string(jstatus));
	}
	if (nullptr != (jstatus=json_object_object_get(json, "param")))
	{
		printf("param: %d\n", json_object_get_boolean(jstatus));
	}
	if (nullptr != (jstatus=json_object_object_get(json, "param2")))
	{
		printf("param2: %d\n", json_object_get_boolean(jstatus));
	}
	if (nullptr != (jstatus=json_object_object_get(json, "param3")))
	{
		printf("param3: %s\n", json_object_get_string(jstatus));
	}
}


int main()
{
	auto server = new ipc::server_service("test", &server_cb);
	server->start();
	
	while (!server->m_shutdown)
	{
		sleep(1);	
	}
	
	delete server;
	
	return 0;
}
