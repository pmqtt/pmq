//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_QOS_HANDLER_FACTORY_HPP
#define PMQ_QOS_HANDLER_FACTORY_HPP

#include <lib/mqtt/mqtt_types.hpp>
#include "qos_handler.hpp"
namespace pmq {
    class qos_handler_factory {
    public:
        qos_handler_factory() = default;
        virtual ~qos_handler_factory() = default;
        virtual std::shared_ptr<pmq::qos_handler> create(const pmq::u_int16 & qos);

    };
}


#endif //PMQ_QOS_HANDLER_FACTORY_HPP
