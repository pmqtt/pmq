//
// Created by pmqtt on 2019-06-29.
//

#ifndef PMQ_CLIENT_HANDLER_HPP
#define PMQ_CLIENT_HANDLER_HPP

#include "lib/exception/bad_connection_exception.hpp"
#include "startup_configuration.hpp"
#include "lib/storage/storage.hpp"

#include "lib/mqtt/control_packet_type.hpp"
#include "lib/mqtt/mqtt_message.hpp"
#include "lib/mqtt/mqtt_package.hpp"
#include "lib/mqtt/mqtt_static_package.hpp"
#include "lib/mqtt/mqtt_connection_info.hpp"
#include "lib/mqtt/mqtt_visitor.hpp"
#include "lib/mqtt/mqtt_publish.hpp"
#include "lib/mqtt/mqtt_subscribe.hpp"
#include "lib/network/socket.hpp"
#include "lib/qos/qos_handler_factory.hpp"
#include "lib/server/login/login_factory.hpp"

namespace pmq{

    class client_handler : public pmq::mqtt_visitor{
    private:
        std::shared_ptr<pmq::login_factory> login_creator;
        std::shared_ptr<pmq::qos_handler_factory>  qos_factory;
        std::shared_ptr<pmq::storage> storage_service;
        pmq::config config;
        std::string client_id;
    public:
        client_handler(const std::shared_ptr<pmq::login_factory> & login_fac,
                       const std::shared_ptr<pmq::qos_handler_factory> & qos_factory,
                       const std::shared_ptr<pmq::storage> & storage_service,
                       const pmq::config & cfg
                       )
            :login_creator(login_fac),qos_factory(qos_factory),storage_service(storage_service),config(cfg){

        }
        ~client_handler() override = default;

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
        void visit(mqtt_controll_package<144, 3> *msg) override;
        void visit(pmq::mqtt_puback *msg) override;

        void handleDisconnect() override ;

        void handle_config_subscription(const std::string & topic);

    };

}

#endif //PMQ_CLIENT_HANDLER_HPP
