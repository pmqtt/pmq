//
// Created by PMQTT on 2019-03-03.
//
#include <functional>
#include <lib/exception/login_exception.hpp>
#include "lib/exception/bad_connection_exception.hpp"
#include "lib/network/client_factory.hpp"
#include "lib/server/server.hpp"




pmq::server::~server() {
    clean_up();
}

void pmq::server::run(std::unique_ptr<pmq::client_factory> && socket_factory){

    while(this->should_service_run){
        try {
            std::function<void(std::shared_ptr<pmq::socket> &)> f([&](std::shared_ptr<pmq::socket> &socket) {
                this->process(socket);
            });
            auto client = socket_factory->create_client_thread(f);
            this->client_threads.emplace_back(client);
        }catch ( const std::exception & e){
            BOOST_LOG_TRIVIAL(error) << e.what();
        }
    }
    clean_up();
}


void pmq::server::process(std::shared_ptr<pmq::socket> & socket) {
    auto client_info = this->server_info->add_new_client_info();
    try {
        client_info->connection_info->connection_socket = socket;

        pmq::mqtt_message message(socket);

        std::shared_ptr<pmq::mqtt_package> package = message.create_package(client_info->connection_info);
        package->accept(*(handler.get()));

        while (socket->is_connected()) {
            std::shared_ptr<pmq::mqtt_package> action_package = message.create_package(client_info->connection_info);
            action_package->accept(*(handler.get()));
        }
    }catch(const pmq::exception::bad_connection_exception & e){
        BOOST_LOG_TRIVIAL(info)<<e.what();
        pmq::mqtt_disconnect disconnect(socket);
        disconnect.send();
    }
    catch (pmq::exception::socket_exception &e) {
        BOOST_LOG_TRIVIAL(info) << "Client closed the connection: " << e.what();
        handler->handleDisconnect();
    }catch (const pmq::exception::login_exception & e){
        BOOST_LOG_TRIVIAL(info)<<e.what();
        handler->handleDisconnect();
    }catch(...){
        BOOST_LOG_TRIVIAL(info)<<"Unknown exception";
        handler->handleDisconnect();
    }
}

void pmq::server::clean_up() {

}


