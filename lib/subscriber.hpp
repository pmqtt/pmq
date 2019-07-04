//
// Created by PMQTT on 2019-05-03.
//

#ifndef PMQ_SUBSCRIBER_HPP
#define PMQ_SUBSCRIBER_HPP
#include "mqtt_types.hpp"
namespace pmq{
    class subscriber{
    public:
        subscriber(const std::shared_ptr<pmq::socket> & socket,const std::string & topic, pmq::u_int16 qos);
        subscriber(const subscriber & rhs);
        subscriber(subscriber && rhs);
        subscriber & operator=(const subscriber & rhs);
        subscriber & operator=(const subscriber && rhs);

        constexpr pmq::u_int8 get_qos()const{ return qos; }
        const std::string & get_topic()const { return topic; }
        void operator<<(const std::string & publish_message );

    private:
        std::shared_ptr<pmq::socket> socket;
        std::string topic;
        pmq::u_int16 qos;
    };

}
#endif //PMQ_SUBSCRIBER_HPP
