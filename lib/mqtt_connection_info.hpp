//
// Created by PMQTT on 2019-04-12.
//

#ifndef PMQ_MQTT_CONNECTION_INFO_HPP
#define PMQ_MQTT_CONNECTION_INFO_HPP
#include "lib/socket.hpp"
namespace pmq {
    enum ConnectionState{
        NOT_CONNECTED = 0,
        CONNECTED = 1
    };
    struct mqtt_connection_info {
        mqtt_connection_info(){
            this->state = ConnectionState::NOT_CONNECTED;
        }
        [[nodiscard]] constexpr bool is_valid()const{
            return this->state == ConnectionState::CONNECTED;
        }
        void set_client_id(const std::string id){
            if(state==ConnectionState::NOT_CONNECTED) {
                this->client_id = id;
                this->state = ConnectionState::CONNECTED;
            }
        }
        ConnectionState state;
        std::string client_id;
        std::shared_ptr<pmq::socket> connection_socket;
    };
}
#endif //PMQ_MQTT_CLIENT_INFO_HPP
