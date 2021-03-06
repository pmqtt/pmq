//
// Created by PMQTT on 2019-04-04.
//

#ifndef PMQ_MQTT_EXCEPTION_HPP
#define PMQ_MQTT_EXCEPTION_HPP

#include <exception>
#include <string_view>

namespace pmq::exception{
    class mqtt_exception : public std::exception{
    public:
        mqtt_exception(const std::string_view & msg) :msg(msg) {

        }
        virtual ~mqtt_exception() {

        }
        virtual const char* what() const noexcept {
            return msg.data();
        }
    private:
        std::string_view msg;
    };
}






#endif //PMQ_MQTT_EXCEPTION_HPP
