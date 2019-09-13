//
// Created by pmqtt on 2019-07-15.
//
#include "message.hpp"

namespace pmq{
    message::message(const std::string &topic, const std::string msg, pmq::QOS qos)
     : topic(topic),msg(msg),qos(qos){

    }

    message::~message() = default;

    message::message(const pmq::message &rhs)
        : topic(rhs.topic),msg(rhs.msg),qos(rhs.qos) {}

    message::message(pmq::message &&rhs)
        :topic(std::move(rhs.topic)),msg(std::move(rhs.msg)),qos(rhs.qos){

    }

    message & message::operator=(pmq::message &&rhs) {
        if(this != &rhs){
            topic = std::move(rhs.topic);
            msg = std::move(rhs.msg);
            qos = rhs.qos;
        }
        return *this;
    }

    message& message::operator=(const pmq::message &rhs) {
        if(this != &rhs){
            topic = rhs.topic;
            msg = rhs.msg;
            qos = rhs.qos;
        }
        return *this;
    }



}
