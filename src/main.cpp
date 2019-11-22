#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <lib/qos_handler_factory.hpp>
#include <thread>


#include "header/client_creator.hpp"
#include "header/client_handler.hpp"
#include "header/http_rest_server.hpp"
#include "header/in_memory_storage.hpp"
#include "header/PMQConfigure.hpp"
#include "header/security.hpp"
#include "header/server.hpp"
#include "header/startup_configuration.hpp"
#include "header/storage.hpp"
#include "header/ssl_client_factory.hpp"
#include "header/tcp_client_factory.hpp"




std::shared_ptr<pmq::client_factory>  create_ssl_client_factory(const pmq::config & cfg){
    return std::make_shared<pmq::ssl_client_factory>(cfg);
}
std::shared_ptr<pmq::client_factory>  create_tcp_client_factory(const pmq::config & cfg){
    return std::make_shared<pmq::tcp_client_factory>(cfg);
}


void init_rest_api(pmq::server & server,pmq::config & conf,std::shared_ptr<pmq::storage> & storage_service){
    const std::string rest_api_address = "http://localhost:"+std::to_string(conf.get_rest_port());
    BOOST_LOG_TRIVIAL(info)<< "START REST API: "<< rest_api_address;
    pmq::on_initialize(rest_api_address,storage_service);
}

int main(int argc,char **argv,char **envp){

    pmq::config conf = parse_program_options(argc,argv);
    BOOST_LOG_TRIVIAL(info)<<"Start PMQ "<<VERSION;
    pmq::ring_zero::clean_argv(argc,&argv);
    pmq::ring_zero::clean_environment(&envp);


    pmq::client_creator creator;
    creator.bind_creator("TCP",create_tcp_client_factory);
    creator.bind_creator("TLS",create_ssl_client_factory);

    std::shared_ptr<pmq::login_factory> login_creator = std::make_shared<pmq::login_factory>();
    std::shared_ptr<pmq::storage> storage_service = std::make_shared<pmq::in_memory_storage>();
    storage_service->insert_configuration_for_subscribers(conf.get_client_config());

    std::shared_ptr<pmq::qos_handler_factory> qos_factory = std::make_shared<pmq::qos_handler_factory>();
    std::shared_ptr<pmq::mqtt_visitor> handler = std::make_shared<pmq::client_handler>(
            login_creator,
            qos_factory,
            storage_service,
            conf
    );


    pmq::server server(handler);
    auto rest_api_func = std::bind(&init_rest_api, std::ref(server), std::ref(conf), std::ref(storage_service));
    std::thread rest_api_thread(rest_api_func);
    try {
        std::shared_ptr<pmq::client_factory> client_factory = creator.get(conf.get_connection_type())(conf);
        server.run(client_factory);
    }catch (const pmq::exception::config_exception & e){
        std::cout<<e.what()<<std::endl;
        pmq::on_shutdown();
    }
    rest_api_thread.join();

    return 0;
}