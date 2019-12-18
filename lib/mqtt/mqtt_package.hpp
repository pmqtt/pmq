//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_MQTT_PACKAGE_HPP
#define PMQ_MQTT_PACKAGE_HPP

#include <cstddef>
#include <string>

#include "mqtt_types.hpp"
#include "mqtt_visitor.hpp"
#include "lib/network/socket.hpp"

namespace pmq {
    class mqtt_package {
    public:
        mqtt_package() = default;
        mqtt_package(std::shared_ptr<pmq::socket> & client_socket) : client_socket(client_socket){}
        virtual ~mqtt_package() = default;
        virtual std::size_t get_payload_length() const = 0;
        virtual void parse(const std::string &payload) = 0;
        virtual void send(){}
        std::string read_string(const std::string & payload,std::size_t & byte_index);

        [[nodiscard]] constexpr pmq::u_int16 calculate_index_from_msb_lsb(pmq::u_int8 msb, pmq::u_int8 lsb)const{
            pmq::u_int16 res = msb<<8;
            res += lsb;
            return res;
        }

        virtual void accept(mqtt_visitor & visitor) = 0;
        std::shared_ptr<pmq::socket> get_socket()const{
            return this->client_socket;
        }
    protected:
        std::shared_ptr<pmq::socket> client_socket;
    };





}


#endif //PMQ_MQTT_PACKAGE_HPP
