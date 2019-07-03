#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "header/client_handler.hpp"
#include <header/tcp_client_factory.hpp>
#include <header/ssl_client_factory.hpp>
#include "header/null_deleter.hpp"
#include "header/PMQConfigure.hpp"
#include "header/http_rest_server.hpp"
#include "header/security.hpp"
#include "header/server.hpp"
#include "header/startup_configuration.hpp"
#include "header/storage.hpp"
#include "header/in_memory_storage.hpp"





void init_rest_api(pmq::server & server,pmq::config & conf,std::shared_ptr<pmq::storage> & storage_service){
    BOOST_LOG_TRIVIAL(info)<< "START REST API: "<<"http://localhost:"+std::to_string(conf.get_rest_port());
    pmq::on_initialize("http://localhost:"+std::to_string(conf.get_rest_port()),storage_service);

}

int main(int argc,char **argv,char **envp){

    pmq::config conf = parse_program_options(argc,argv);
    BOOST_LOG_TRIVIAL(info)<<"Start PMQ "<<VERSION;
    pmq::ring_zero::clean_argv(argc,&argv);
    pmq::ring_zero::clean_environment(&envp);

    std::shared_ptr<pmq::storage> storage_service = std::make_shared<pmq::in_memory_storage>();
    std::shared_ptr<pmq::mqtt_visitor> handler = std::make_shared<pmq::client_handler>(storage_service,conf);


    pmq::server server(handler);
    auto rest_api_func = std::bind(&init_rest_api, std::ref(server), std::ref(conf), std::ref(storage_service));
    boost::thread rest_api_thread(rest_api_func);
    try {
        if (conf.should_use_tls()) {
            auto client_factory = pmq::ssl_client_factory(conf);
            server.run(client_factory);
        } else {
            auto client_factory = pmq::tcp_client_factory(conf);
            server.run(client_factory);
        }

    }catch (const pmq::exception::config_exception & e){
        std::cout<<e.what()<<std::endl;
        pmq::on_shutdown();
    }
    rest_api_thread.join();



    return 0;
}