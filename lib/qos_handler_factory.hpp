//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_QOS_HANDLER_FACTORY_HPP
#define PMQ_QOS_HANDLER_FACTORY_HPP

#include "qos_handler.hpp"
#include "mqtt_types.hpp"
namespace pmq {
    class qos_handler_factory {
    public:
        qos_handler_factory() = default;
        virtual ~qos_handler_factory() = default;
        virtual std::shared_ptr<pmq::qos_handler> create(pmq::QOS qos);

    };
}


#endif //PMQ_QOS_HANDLER_FACTORY_HPP
