//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_QOS_TWO_HANDLER_HPP
#define PMQ_QOS_TWO_HANDLER_HPP

#include "qos_handler.hpp"
namespace pmq {
    class qos_two_handler : public qos_handler {
    public:
        qos_two_handler() = default;
        virtual ~qos_two_handler() = defualt;

        void handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) override;
    };
}

#endif //PMQ_QOS_TWO_HANDLER_HPP
