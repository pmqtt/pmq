//
// Created by pmqtt on 2019-06-16.
//
#include "tcp_client_factory.hpp"
namespace pmq{
    tcp_client_factory::tcp_client_factory(const pmq::config & cfg)
            : config(cfg) {
    }
    tcp_client_factory::~tcp_client_factory() = default;
    std::shared_ptr<std::thread> tcp_client_factory::create_client_thread(std::function< void(std::shared_ptr<socket>&)> & process) {
        std::shared_ptr<pmq::socket> socket = create_socket();
        create_acceptor(socket);
        if(pmq::detail::is_ssl_handshake(socket.get())){
            throw pmq::exception::socket_exception("TLS connection detected but only plain socket configured");
        }
        auto f = std::bind(process,socket);
        return std::make_shared<std::thread>(f);
    }
}
