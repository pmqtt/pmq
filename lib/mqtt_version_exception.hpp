//
// Created by PMQTT on 2019-04-04.
//

#ifndef PMQ_MQTT_VERSION_EXCEPTION_HPP
#define PMQ_MQTT_VERSION_EXCEPTION_HPP

#include <exception>
#include <string_view>

#include "lib/mqtt_exception.hpp"

namespace pmq::exception{
class mqtt_version_exception : public mqtt_exception{
    public:
        explicit mqtt_version_exception(const std::string_view & msg) :mqtt_exception(msg) {

        }
        ~mqtt_version_exception() override = default;

    private:

    };
}




#endif //PMQ_MQTT_EXCEPTION_HPP
