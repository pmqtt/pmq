//
// Created by pmqtt on 2019-07-16.
//

#include "mqtt_types.hpp"
namespace pmq {
    pmq::QOS create_qos_from_int(unsigned int q) {
        if (q == 0) return pmq::QOS_0;
        if (q == 1) return pmq::QOS_1;
        if (q == 2) return pmq::QOS_2;
        return pmq::INVALID_QOS;
    }

}