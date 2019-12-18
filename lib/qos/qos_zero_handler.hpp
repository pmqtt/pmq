//
// Created by pmqtt on 2019-07-06.
//

#ifndef PMQ_QOS_ZERO_HANDLER_HPP
#define PMQ_QOS_ZERO_HANDLER_HPP

#include "qos_handler.hpp"
namespace pmq {

    class qos_zero_handler : public qos_handler {
    public:
        qos_zero_handler() = default;
        virtual ~qos_zero_handler() = default;

        void handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) override;

    };
}


#endif //PMQ_QOS_ZERO_HANDLER_HPP
