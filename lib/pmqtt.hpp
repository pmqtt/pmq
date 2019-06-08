//
// Created by PMQTT on 2019-04-03.
//

#ifndef PMQ_PMQTT_HPP
#define PMQ_PMQTT_HPP
#include <string>
#include "mqtt_types.hpp"
#include "mqtt_version_exception.hpp"
namespace pmq {

    struct mqtt_api {
        virtual std::string get_mqtt_name() const = 0;

        virtual pmq::u_int8 get_version() const = 0;
    };

    struct mqtt_api3 : public mqtt_api {
        std::string get_mqtt_name() const override {
            return "MQIsdp";
        }

        pmq::u_int8 get_version() const override {
            return 3;
        }
    };

    struct mqtt_api4 : public mqtt_api {
        std::string get_mqtt_name() const override {
            return "MQTT";
        }

        pmq::u_int8 get_version() const override {
            return 4;
        }
    };

    struct mqtt_api5 : public mqtt_api {
        std::string get_mqtt_name() const override {
            return "MQTT";
        }

        pmq::u_int8 get_version() const override {
            return 5;
        }
    };

    static std::shared_ptr<mqtt_api> mqtt_api_factory(const std::string & mqtt_version_str,pmq::u_int8 version){
        if( version == 3 && mqtt_version_str == "MQIsdp" ){
            return std::shared_ptr<mqtt_api3>();
        }
        if( version == 4 && mqtt_version_str == "MQTT" ){
            return std::shared_ptr<mqtt_api4>();
        }
        if( version == 5 && mqtt_version_str == "MQTT" ){
            return std::shared_ptr<mqtt_api5>();
        }
        throw pmq::exception::mqtt_version_exception("Incompatible version");
    }

}


#endif //PMQ_PMQTT_HPP
