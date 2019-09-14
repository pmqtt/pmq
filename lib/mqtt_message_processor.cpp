//
// Created by pmqtt on 2019-09-14.
//
#include "lib/mqtt_message_processor.hpp"

std::string pmq::detail::encode(unsigned int length){
    std::string res;
    do {
        unsigned char encoded_byte = length % 128;
        length = length / 128;
        // if there are more data to encode, set the top bit of this byte
        if (length > 0)
            encoded_byte = encoded_byte | static_cast<unsigned int>(128);
        res += encoded_byte;
    }while (length > 0);
    return res;
}
