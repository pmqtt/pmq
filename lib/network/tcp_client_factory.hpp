//
// Created by pmqtt on 2019-06-16.
//

#ifndef PMQ_TCP_CLIENT_FACTORY_HPP
#define PMQ_TCP_CLIENT_FACTORY_HPP
#include <lib/exception/acceptor_exception.hpp>
#include "client_factory.hpp"
#include <lib/server/startup_configuration.hpp>
#include <boost/asio/io_context.hpp>


#include <string>
namespace pmq{
    class tcp_client_factory : public client_factory{
    public:
        tcp_client_factory(const pmq::config & cfg);

        virtual ~tcp_client_factory();
        std::shared_ptr<std::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) override;

    private:
        void create_acceptor(std::shared_ptr<pmq::socket> & socket){
         try{
            tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),config.get_port()));
            acceptor.accept(*socket->get_inner_socket());
         }catch( const boost::system::system_error & e ){
            throw pmq::exception::acceptor_exception("Listening on port "
                                                     + std::to_string(config.get_port())
                                                     + " not established -"
                                                     + std::to_string(e.code().value())
                                                     + " - Error message : "
                                                     + e.what());
            }
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
