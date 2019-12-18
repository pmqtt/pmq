//
// Created by pmqtt on 2019-06-16.
//
#include <lib/network/tcp_client_factory.hpp>
namespace pmq{
    tcp_client_factory::tcp_client_factory(const pmq::config & cfg)
            : config(cfg) {
    }
    tcp_client_factory::~tcp_client_factory() = default;
    std::shared_ptr<std::thread> tcp_client_factory::create_client_thread(std::function< void(std::shared_ptr<socket>&)> & process) {
        std::shared_ptr<pmq::socket> socket = create_socket();
        create_acceptor(socket);
        auto f = std::bind(process,socket);
        return std::make_shared<std::thread>(f);
    }
}
