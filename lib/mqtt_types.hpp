//
// Created by Michael Burzan on 2019-03-28.
//

#ifndef PMQ_MQTT_TYPES_HPP
#define PMQ_MQTT_TYPES_HPP
namespace pmq{
    typedef unsigned char  u_int8;
    typedef unsigned short u_int16;

    enum QOS{
        QOS_0 = 0,
        QOS_1 = 1,
        QOS_2 = 2,
    };

}
#endif //PMQ_MQTT_TYPES_HPP
