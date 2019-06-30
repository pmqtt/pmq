//
// Created by PMQTT on 2019-03-03.
//
#include "header/bad_connection_exception.hpp"
#include "header/client_factory.hpp"
#include "header/tcp_client_factory.hpp"
#include "header/server.hpp"
#include "header/ssl_client_factory.hpp"

#include <functional>
#include <list>
#include <map>
#include <string>
#include <header/acceptor_exception.hpp>
#include <header/tls_handshake_exception.hpp>




pmq::server::~server() {
    clean_up();
}

void pmq::server::run(pmq::client_factory & socket_factory){

    while(this->should_service_run){
        try {
            std::function<void(std::shared_ptr<pmq::socket> &)> f([&](std::shared_ptr<pmq::socket> &socket) {
                this->process(socket);
            });
            auto client = socket_factory.create_client_thread(f);
            this->client_threads.emplace_back(client);
        }catch ( const std::exception & e){
            BOOST_LOG_TRIVIAL(error) << e.what();
        }
    }
    clean_up();
}


void pmq::server::process(std::shared_ptr<pmq::socket> & socket) {
    try {
        auto client_info = this->server_info->add_new_client_info();
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
    }
}

void pmq::server::clean_up() {

}


