//
// Created by pmqtt on 2019-07-15.
//

#ifndef PMQ_MESSAGE_HPP
#define PMQ_MESSAGE_HPP

#include <string>
#include "mqtt_types.hpp"

namespace pmq{
    class message{
    public:
        message(const std::string & topic,const std::string &msg,pmq::QOS qos);
        virtual ~message();
        message()= default;
        message(const message & rhs);
        message(message && rhs);
        message &operator=(const message & rhs);
        message &operator=(message && rhs);

        const std::string & get_payload()const{
            return msg;
        }
        const std::string & get_topic()const{
            return topic;
        }
        pmq::QOS get_qos()const{
            return qos;
        }

    private:
        std::string topic="";
        std::string msg="";
        pmq::QOS qos;

    };
}

#endif //PMQ_MESSAGE_HPP
