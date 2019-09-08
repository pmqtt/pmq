//
// Created by pmqtt on 2019-09-08.
//

#ifndef PMQ_MQTT_MESSAGE_PROCESSOR_HPP
#define PMQ_MQTT_MESSAGE_PROCESSOR_HPP
/*#include <memory>
#include <string>

namespace pmq::detail {
    template<class T>
    unsigned int read_length(std::shared_ptr<T> &reader) {
        unsigned int value = 0;
        unsigned int multiplier = 1;
        unsigned char encoded_byte = 0;
        do {
            encoded_byte = reader->read(1)[0];
            value += (encoded_byte & static_cast<unsigned int>(127)) * multiplier;
            multiplier *= static_cast<unsigned int>(128);
        } while ((encoded_byte & static_cast<unsigned int>(128)) != 0);
        return value;
    }

    std::string encode(unsigned int length){
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

}*/


#endif //PMQ_MQTT_MESSAGE_PROCESSOR_HPP
