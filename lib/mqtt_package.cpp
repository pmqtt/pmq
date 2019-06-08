//
// Created by Michael Burzan on 2019-03-28.
//
#include <boost/log/trivial.hpp>
#include "lib/mqtt_package.hpp"
#include "lib/mqtt_types.hpp"


unsigned int pmq::mqtt_package::read_length(){
    unsigned int value =0;
    unsigned int multiplier = 1;
    unsigned char encoded_byte = 0;
    do{
        encoded_byte = this->client_socket->read(1)[0];
        value += (encoded_byte & 127) * multiplier;
        multiplier *= 128;
    }while((encoded_byte & 128) !=0);
    return value;
}

std::string pmq::mqtt_package::encode(unsigned int length)const{
    std::string res;
    do {
        unsigned char encoded_byte = length % 128;
        length = length / 128;
        // if there are more data to encode, set the top bit of this byte
        if (length > 0)
            encoded_byte = encoded_byte | 128;
        res += encoded_byte;
    }while (length > 0);
    return res;
}


std::string pmq::mqtt_package::read_string(const std::string & payload,std::size_t & byte_index){
    pmq::u_int8  strlen_msb = payload[byte_index++];
    pmq::u_int8  strlen_lsb = payload[byte_index++];
    pmq::u_int16 str_len = this->calculate_index_from_msb_lsb(strlen_msb, strlen_lsb);

    std::string res =  payload.substr(byte_index, str_len );
    byte_index += str_len;
    return res;
}

