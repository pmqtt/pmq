//
// Created by pmqtt on 2019-06-23.
//

#ifndef PMQ_SSL_CLIENT_FACTORY_HPP
#define PMQ_SSL_CLIENT_FACTORY_HPP
#include "client_factory.hpp"
#include "startup_configuration.hpp"
namespace pmq{
    class ssl_client_factory : public client_factory{
    public:
        ssl_client_factory(std::size_t port,const pmq::config & cfg);
        virtual ~ssl_client_factory();
        std::shared_ptr<boost::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) override;
        std::string get_password()const;
    private:
        boost::asio::io_context context;
        boost::asio::ssl::context ssl_contex;

        std::size_t port;
    };
}

#endif //PMQ_SSL_CLIENT_FACTORY_HPP
