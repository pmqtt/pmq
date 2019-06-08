//
// Created by PMQTT on 2019-04-12.
//

#ifndef PMQ_MQTT_CONNECTION_INFO_HPP
#define PMQ_MQTT_CONNECTION_INFO_HPP
#include "lib/socket.hpp"
namespace pmq {
    struct mqtt_connection_info {
        std::string client_id;
        std::shared_ptr<pmq::socket> connection_socket;
    };
}
#endif //PMQ_MQTT_CLIENT_INFO_HPP
