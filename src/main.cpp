#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/program_options.hpp>
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




pmq::config parse_program_options(int argc,char **argv){
    boost::program_options::options_description desc{"Options"};
    desc.add_options()
            ("help,h", "Help screen")
            ("version,v", "print version")
            ("port,p", boost::program_options::value<int>()->default_value(1883) ,"MQTT Broker port")
            ("rest-port,rp",boost::program_options::value<int>()->default_value(1884) ,"REST Interface port")
            ("tls-certificate",boost::program_options::value<std::string>(),"TLS certificate file")
            ("tls-private-key",boost::program_options::value<std::string>(),"TLS private key")
            ("tls-dh-file",boost::program_options::value<std::string>(),"Diffie-Hellman file")
            ("anonymous-login",boost::program_options::value<bool>()->default_value(true),"Allow or permit anoymous connection. Default is true")
            ;

    boost::program_options::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        exit(0);
    }
    if (vm.count("version")) {
        std::cout << "PMQ 2019 - v" << VERSION <<" - " <<std::endl;
        exit(0);
    }
    pmq::config conf;
    if(vm.count("port")){
        conf.set_port(vm["port"].as<int>());
    }
    if(vm.count("rest-port")){
        conf.set_rest_port(vm["rest-port"].as<int>());
    }
    if(vm.count("tls-certificate")){
        conf.set_tls_cert_path(vm["tls-certificate"].as<std::string>());
    }
    if(vm.count("tls-private-key")){
        conf.set_tls_private_key(vm["tls-private-key"].as<std::string>());
    }
    if(vm.count("tls-dh-file")){
        conf.set_tls_dh_file(vm["tls-dh-file"].as<std::string>());
    }
    if(vm.count("anonymous-login")){
        conf.set_allow_anonymous_login(vm["anonymous-login"].as<bool>());
    }

    return conf;
}

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