//
// Created by pmqtt on 2019-06-29.
//

#ifndef PMQ_CLIENT_HANDLER_HPP
#define PMQ_CLIENT_HANDLER_HPP

#include "bad_connection_exception.hpp"
#include "startup_configuration.hpp"
#include "storage.hpp"

#include "lib/control_packet_type.hpp"
#include "lib/mqtt_message.hpp"
#include "lib/mqtt_package.hpp"
#include "lib/mqtt_static_package.hpp"
#include "lib/mqtt_connection_info.hpp"
#include "lib/mqtt_visitor.hpp"
#include "lib/mqtt_publish.hpp"
#include "lib/mqtt_subscribe.hpp"
#include "lib/socket.hpp"
#include "lib/qos_handler_factory.hpp"

namespace pmq{

    class client_handler : public pmq::mqtt_visitor{
    private:
        std::shared_ptr<pmq::qos_handler_factory>  qos_factory;
        std::shared_ptr<pmq::storage> storage_service;
        pmq::config config;
        std::string client_id;
    public:
        client_handler(const std::shared_ptr<pmq::qos_handler_factory> & qos_factory,const std::shared_ptr<pmq::storage> & storage_service,const pmq::config & cfg)
            : qos_factory(qos_factory),storage_service(storage_service),config(cfg){

        }
        virtual ~client_handler(){}

        void visit(mqtt_connect *msg) override;
        void visit(mqtt_publish *msg) override;
        void visit(mqtt_subscribe *msg) override;
        void visit(mqtt_static_package<192, 0> *msg) override;
        void visit(mqtt_static_package<208, 0> *msg) override;
        void visit(mqtt_static_package<224, 0> *msg) override;
        void visit(mqtt_controll_package<112, 2> *msg) override;
        void visit(mqtt_controll_package<80, 2> *msg) override;
        void visit(mqtt_controll_package<98, 2> *msg) override;
        void visit(mqtt_controll_package<32, 2> *msg) override;
        void visit(mqtt_controll_package<176, 2> *msg) override;
        void visit(mqtt_controll_package<144, 2> *msg) override;
        void visit(pmq::mqtt_puback *msg) override;

    };

}

#endif //PMQ_CLIENT_HANDLER_HPP
