//
// Created by pmqtt on 2019-06-16.
//

#ifndef PMQ_TCP_CLIENT_FACTORY_HPP
#define PMQ_TCP_CLIENT_FACTORY_HPP
#include "client_factory.hpp"
#include "startup_configuration.hpp"
namespace pmq{
    class tcp_client_factory : public client_factory{
    public:
        tcp_client_factory(const pmq::config & cfg);

        virtual ~tcp_client_factory();
        std::shared_ptr<boost::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) override;

    private:
        void create_acceptor(std::shared_ptr<pmq::socket> & socket){
            tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),config.get_port()));
            acceptor.accept(*socket->get_inner_socket());
        }

        std::shared_ptr<pmq::socket>  create_socket(){
            std::shared_ptr<pmq::socket> socket = std::make_shared<pmq::socket>(new tcp::socket(context));
            return socket;
        }
    private:

        boost::asio::io_context context;
        pmq::config config;
    };
}


#endif //PMQ_TCP_CLIENT_FACTORY_HPP
