//
// Created by Michael Burzan on 2019-05-26.
//

#ifndef PMQ_CONNECTION_PARAMETER_HPP
#define PMQ_CONNECTION_PARAMETER_HPP
#include "pmqtt.hpp"
namespace pmq {


    class connection_parameter {
    public:
        connection_parameter(std::shared_ptr<pmq::mqtt_api> & api) : api(api){};
        virtual ~connection_parameter();
        std::string get_protocol_name()const{
            return this->api->get_mqtt_name();
        }
        pmq::u_int8 get_protocol_version()const{
            this->api->get_version();
        }


    protected:
        std::shared_ptr<pmq::mqtt_api> api;
        unsigned int version;
        unsigned int keep_alive;
        bool user_name_flag;
        bool password_flag;
        bool will_retain;
        std::size_t will_qos;
        bool will_flag;
        bool clean_start;
        bool reserved;
        std::string client_id;
        std::string will_topic;
        std::string will_payload;
        std::string user_name;
        std::string password;
    };

}

#endif //PMQ_CONNECTION_PARAMETER_HPP
