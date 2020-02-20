#include <unistd.h>

#include "client_service.hpp"


void client_cb(json_object *json)
{
    json_object *jstatus;

    if (json == nullptr)
    {
        std::cout << "Input parameter null." << std::endl;
        return;
    }

    std::cout << "client cb." << std::endl;

    if (nullptr != (jstatus=json_object_object_get(json, "status")))
    {
        std::cout << "status: " << json_object_get_int(jstatus) << std::endl;
    }
    if (nullptr != (jstatus=json_object_object_get(json, "operation")))
    {
        std::cout << "operation: " << json_object_get_string(jstatus) << std::endl;
    }
    if (nullptr != (jstatus=json_object_object_get(json, "param")))
    {
        std::cout << "param: " << json_object_get_boolean(jstatus) << std::endl;
    }
    if (nullptr != (jstatus=json_object_object_get(json, "param2")))
    {
        std::cout << "param2: " << json_object_get_boolean(jstatus) << std::endl;
    }
    if (nullptr != (jstatus=json_object_object_get(json, "param3")))
    {
        std::cout << "param3: " << json_object_get_string(jstatus) << std::endl;
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
        std::cout << "server.send() error." << std::endl;
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
