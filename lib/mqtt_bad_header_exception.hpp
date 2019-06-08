//
// Created by Michael Burzan on 2019-04-13.
//

#ifndef PMQ_MQTT_BAD_HEADER_EXCEPTION_HPP
#define PMQ_MQTT_BAD_HEADER_EXCEPTION_HPP


#include <exception>
#include <string_view>

#include "lib/mqtt_exception.hpp"
namespace pmq {
    namespace exception {
        class mqtt_bad_header_exception : public mqtt_exception {
        public:
            mqtt_bad_header_exception(const std::string_view &msg) : mqtt_exception(msg) {

            }

            virtual ~mqtt_bad_header_exception() {

            }

        private:

        };
    }
}
#endif //PMQ_MQTT_BAD_HEADER_EXCEPTION_HPP
