//
// Created by PMQTT on 2019-03-28.
//
#include <boost/log/trivial.hpp>
#include <lib/detail/mqtt_message_processor.hpp>

#include "mqtt_package.hpp"
#include "mqtt_types.hpp"

std::string pmq::mqtt_package::read_string(const std::string & payload,std::size_t & byte_index){
    pmq::u_int8  strlen_msb = payload[byte_index++];
    pmq::u_int8  strlen_lsb = payload[byte_index++];
    pmq::u_int16 str_len = this->calculate_index_from_msb_lsb(strlen_msb, strlen_lsb);

    std::string res =  payload.substr(byte_index, str_len );
    byte_index += str_len;
    return res;
}

