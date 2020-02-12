#include <unistd.h>

#include "client_service.hpp"


void client_cb(json_object *json)
{
	json_object *jstatus;
	
	if (json == nullptr)
	{
		printf("Input parameter null\n");
		return;	
	}

	printf("client cb\n");	
	
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


int main(void)
{
	json_object *json;
	
	auto client = new ipc::client_service(&client_cb);

	json = json_object_new_object();
	json_object_object_add(json, "status", json_object_new_int(200));
	json_object_object_add(json, "operation", json_object_new_string("get"));
	json_object_object_add(json, "param", json_object_new_boolean(0));
	json_object_object_add(json, "param2", json_object_new_boolean(1));
	json_object_object_add(json, "param3", json_object_new_string("bang"));

	if (client->client_send("test", json) !=0 )
	{
		printf("server.send() error.\n");
		return -1;	
	}

	while (!client->m_shutdown)
	{
		sleep(1);	
	}

	json_object_put(json);
	
	delete client;
	
	return 0;
}
