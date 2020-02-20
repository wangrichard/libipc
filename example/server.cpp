#include <unistd.h>

#include "server_service.hpp"

void server_cb(json_object *json)
{
    json_object *jstatus;

    if (json == nullptr)
    {
        std::cout << "Input parameter null." << std::endl;
        return;
    }

    std::cout << "server cb." << std::endl;

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
        std::cout << "param: "<< json_object_get_boolean(jstatus) << std::endl;
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
