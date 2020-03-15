#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <thread>

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




template<class T>
auto && create_connection_fatory(const pmq::config & cfg){
    std::move(std::make_unique<T>(cfg));
}



std::shared_ptr<pmq::client_factory>  create_ssl_client_factory(const pmq::config & cfg){
    return std::make_shared<pmq::ssl_client_factory>(cfg);
}
std::shared_ptr<pmq::client_factory>  create_tcp_client_factory(const pmq::config & cfg){
    return std::make_shared<pmq::tcp_client_factory>(cfg);
}

std::shared_ptr<pmq::client_factory>  create_ssl_client_or_non_ssl_factory(const pmq::config & cfg){
    return std::make_shared<pmq::connection_factory>(cfg);
}

#ifdef RESTAPI
void init_rest_api(pmq::server & server,pmq::config & conf,std::shared_ptr<pmq::storage> & storage_service){
    const std::string rest_api_address = "http://localhost:"+std::to_string(conf.get_rest_port());
    BOOST_LOG_TRIVIAL(info)<< "START REST API: "<< rest_api_address;
    pmq::on_initialize(rest_api_address,storage_service);
}
#endif



int main(int argc,char **argv,char **envp){
    pmq::config conf = parse_program_options(argc,argv);
    BOOST_LOG_TRIVIAL(info)<<"Start PMQ "<<VERSION;
    pmq::ring_zero::clean_argv(argc,&argv);
    pmq::ring_zero::clean_environment(&envp);


    pmq::client_creator creator;
    creator.bind_creator("plain",create_tcp_client_factory);
    creator.bind_creator("tls",create_ssl_client_factory);
    creator.bind_creator("plain-tls",create_ssl_client_or_non_ssl_factory);

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
#ifdef RESTAPI
    BOOST_LOG_TRIVIAL(info)<<"Activate REST interface ...";
    auto rest_api_func = std::bind(&init_rest_api, std::ref(server), std::ref(conf), std::ref(storage_service));
    std::thread rest_api_thread(rest_api_func);
#endif
    try {
        std::shared_ptr<pmq::client_factory> client_factory = creator.get(conf.get_connection_type())(conf);
        server.run(client_factory);
    }catch (const pmq::exception::config_exception & e){
        BOOST_LOG_TRIVIAL(error)<<e.what();
#ifdef RESTAPI
        pmq::on_shutdown();
#endif
    }
#ifdef RESTAPI
    rest_api_thread.join();
#endif

    return 0;
}