//
// Created by pmqtt on 2019-07-07.
//

#include "qos_handler_factory.hpp"
#include "qos_zero_handler.hpp"
#include "qos_one_handler.hpp"
#include "qos_two_handler.hpp"

std::shared_ptr<pmq::qos_handler> pmq::qos_handler_factory::create(const pmq::u_int16 &qos) {
    if(qos == pmq::QOS_0)
        return std::make_shared<pmq::qos_zero_handler>();
    if(qos == pmq::QOS_1)
        return std::make_shared<pmq::qos_one_handler>();
    if(qos == pmq::QOS_2)
        return std::make_shared<pmq::qos_two_handler>();

    return std::shared_ptr<pmq::qos_handler>();
}
