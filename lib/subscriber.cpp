//
// Created by PMQTT on 2019-05-03.
//

#include <string>
#include "control_packet_type.hpp"
#include "mqtt_types.hpp"
#include "socket.hpp"
#include "subscriber.hpp"
namespace {
    std::string encode(unsigned int length){
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

    std::string calculate_msb_lsb(std::size_t len){
        pmq::u_int8 msb = len >> 8;
        pmq::u_int8 lsb = len & 0xFF;
        std::string res;
        res += msb;
        res += lsb;
        return res;
    }

}

namespace pmq{
    subscriber::subscriber(const std::shared_ptr<pmq::socket> &socket, const std::string &topic, pmq::u_int16 qos)
        : socket(socket),topic(topic),qos(qos){
    }
    subscriber::subscriber(const pmq::subscriber &rhs)
        : socket(rhs.socket),topic(rhs.topic),qos(rhs.qos){
    }
    subscriber::subscriber(pmq::subscriber &&rhs)
        : socket(std::move(rhs.socket)),topic(std::move(rhs.topic)), qos(rhs.qos){

    }
    subscriber & subscriber::operator=(const pmq::subscriber &rhs) {
        if(this != &rhs){
            this->socket = rhs.socket;
            this->topic  = rhs.topic;
            this->qos    = rhs.qos;
        }
        return *this;
    }
    subscriber & subscriber::operator=(const pmq::subscriber &&rhs) {
        if(this != &rhs){
            this->socket = std::move(rhs.socket);
            this->topic  = std::move(rhs.topic);
            this->qos    = rhs.qos;
        }
        return *this;
    }
    void subscriber::operator<<(const std::string &publish_message) {
        pmq::u_int8 variable_header_length = 0;
        if(qos > 0){
            variable_header_length += 2; //FOR PACKAGE_IDENT ;
        }
        std::string msg;
        pmq::u_int8 first_byte       = pmq::CONTROL_PACKET_TYPE::PUBLISH <<4;
        std::string topic_length     = calculate_msb_lsb(topic.length());
        std::string message_length   = encode(publish_message.length());
        std::string remaining_length = encode(topic_length.length()    +
                                              message_length.length()  +
                                              publish_message.length() +
                                              topic.length()           +
                                              variable_header_length );


        first_byte = first_byte | qos<<1;

        msg += first_byte;
        msg += remaining_length;
        msg += topic_length;
        msg += topic;
        if(qos > 0){
            BOOST_LOG_TRIVIAL(debug)<<"qos: "<<qos;
            pmq::u_int8 msb = 0;
            pmq::u_int8 lsb = 19;
            msg += msb;
            msg += lsb;
        }
        msg += message_length;
        msg += publish_message;

        this->socket->write(msg);
    }

}