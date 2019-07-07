//
// Created by pmqtt on 2019-07-06.
//

#ifndef PMQ_QOS_HANDLER_HPP
#define PMQ_QOS_HANDLER_HPP
#include "mqtt_package.hpp"
#include "mqtt_publish.hpp"
#include "header/storage.hpp"
namespace pmq{
    class qos_handler{
    public:
        qos_handler()= default;
        virtual ~qos_handler()= default;

    public:
        virtual void handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) = 0;
    };
}

#endif //PMQ_QOS_HANDLER_HPP
