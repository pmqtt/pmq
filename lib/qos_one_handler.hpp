//
// Created by pmqtt on 2019-07-06.
//

#ifndef PMQ_QOS_ONE_HANDLER_HPP
#define PMQ_QOS_ONE_HANDLER_HPP

#include "qos_handler.hpp"
namespace pmq {
    class qos_one_handler : public qos_handler {
    public:
        qos_one_handler() = default;
        virtual ~qos_one_handler() = default;

        void handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) override;

    };

}


#endif //PMQ_QOS_ONE_HANDLER_HPP
