#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <thread>

#include <lib/server/main.hpp>


int main(int argc,char **argv,char **envp){
    pmq::config conf = parse_program_options(argc,argv);
    BOOST_LOG_TRIVIAL(info)<<"Start PMQ "<<VERSION;
    pmq::ring_zero::clean_argv(argc,&argv);
    pmq::ring_zero::clean_environment(&envp);


    pmq::client_creator creator = create_client_creator();


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
        std::unique_ptr<pmq::client_factory> client_factory = creator.get(conf.get_connection_type())(conf);
        server.run(std::move(client_factory));
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