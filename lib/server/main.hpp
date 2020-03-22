//
// Created by pmqtt on 22.03.20.
//

#ifndef PMQ_MAIN_HPP
#define PMQ_MAIN_HPP

#include <lib/qos/qos_handler_factory.hpp>
#include <lib/server/client_creator.hpp>
#include <lib/server/client_handler.hpp>
#include <lib/rest/http_rest_server.hpp>
#include <lib/storage/in_memory_storage.hpp>
#include <lib/server/PMQConfigure.hpp>
#include <lib/server/security.hpp>
#include <lib/server/server.hpp>
#include <lib/server/startup_configuration.hpp>
#include <lib/storage/storage.hpp>
#include <lib/network/ssl_client_factory.hpp>
#include <lib/network/tcp_client_factory.hpp>
#include <lib/network/connection_factory.hpp>


static auto create_plain_connection_fatory(const pmq::config & cfg){
    return std::make_unique<pmq::tcp_client_factory>(cfg);
}

static auto create_ssl_connection_fatory(const pmq::config & cfg){
    return std::make_unique<pmq::tcp_client_factory>(cfg);
}

static auto create_plain_ssl_connection_fatory(const pmq::config & cfg){
    return std::make_unique<pmq::tcp_client_factory>(cfg);
}


static pmq::client_creator create_client_creator(){
    pmq::client_creator creator;
    creator.bind_creator("plain"    , create_plain_connection_fatory);
    creator.bind_creator("tls"      , create_ssl_connection_fatory);
    creator.bind_creator("plain-tls", create_plain_ssl_connection_fatory);
    return creator;
}

std::unique_ptr<pmq::mqtt_visitor> create_client_handler( std::shared_ptr<pmq::storage> storage_service, pmq::config &conf){
    std::shared_ptr<pmq::login_factory> login_creator = std::make_shared<pmq::login_factory>();
    storage_service->insert_configuration_for_subscribers(conf.get_client_config());

    std::shared_ptr<pmq::qos_handler_factory> qos_factory = std::make_shared<pmq::qos_handler_factory>();
    return std::make_unique<pmq::client_handler>(
            login_creator,
            qos_factory,
            storage_service,
            conf
    );
}

#ifdef RESTAPI
static void init_rest_api(pmq::server & server,pmq::config & conf,std::shared_ptr<pmq::storage> & storage_service){
    const std::string rest_api_address = "http://localhost:"+std::to_string(conf.get_rest_port());
    BOOST_LOG_TRIVIAL(info)<< "START REST API: "<< rest_api_address;
    pmq::on_initialize(rest_api_address,storage_service);
}
#endif

#endif //PMQ_MAIN_HPP
