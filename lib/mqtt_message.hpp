//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_MQTT_MESSAGE_HPP
#define PMQ_MQTT_MESSAGE_HPP

#include "lib/mqtt_connection_info.hpp"
#include "socket.hpp"

namespace pmq {
    class mqtt_package;
    class mqtt_message {
    public:


        explicit mqtt_message(std::shared_ptr<pmq::socket> &client_socket) : client_socket(client_socket){

        }


        std::shared_ptr<pmq::mqtt_package> create_package(std::shared_ptr<pmq::mqtt_connection_info> & connection_info);
        unsigned int read_length();


        virtual ~mqtt_message() = default;
    private:
        std::shared_ptr<pmq::socket> client_socket;
    };
}


#endif //PMQ_MQTT_MESSAGE_HPP
