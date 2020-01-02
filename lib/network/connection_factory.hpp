//
// Created by pmqtt on 18.12.19.
//

#ifndef PMQ_CONNECTION_FACTORY_HPP
#define PMQ_CONNECTION_FACTORY_HPP
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <openssl/crypto.h>
#include <lib/exception/tls_handshake_exception.hpp>
#include <lib/exception/acceptor_exception.hpp>
#include <lib/server/startup_configuration.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>
#include "socket.hpp"
#include "socket_functions.hpp"
#include "client_factory.hpp"


namespace pmq{



    class connection_factory : public client_factory{
    public:
        connection_factory(const pmq::config & cfg) : config(cfg),ssl_contex(boost::asio::ssl::context::sslv23){
            if(!cfg.get_tls_cert_path().empty()) {
                try {
                    ssl_contex.set_options(
                            boost::asio::ssl::context::default_workarounds
                            | boost::asio::ssl::context::no_sslv2
                            | boost::asio::ssl::context::single_dh_use);
                    ssl_contex.set_verify_mode(
                            boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);

                    //ssl_contex.set_verify_callback(&verify_certificate_cb);
                    ssl_contex.set_password_callback(boost::bind(&connection_factory::get_password, this));
                    ssl_contex.use_certificate_chain_file(cfg.get_tls_cert_path());

                    ssl_contex.use_private_key_file(cfg.get_tls_private_key(), boost::asio::ssl::context::pem);
                    ssl_contex.use_tmp_dh_file(cfg.get_tls_dh_file());
                } catch (const boost::system::system_error &e) {
                    throw pmq::exception::config_exception(e.what());
                }
            }

        }
        virtual ~connection_factory() = default;
        virtual std::shared_ptr<std::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> &  process){
            try{
                std::shared_ptr<pmq::socket> socket = std::make_shared<pmq::socket>(new tcp::socket(context));
                auto verify_certificate_cb = [&](bool preverified, boost::asio::ssl::verify_context& ctx)->bool{
                    return socket->verify_certificate(preverified,ctx);
                };


                ssl_contex.set_verify_callback(verify_certificate_cb);

                tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),config.get_port()));
                acceptor.accept(*socket->get_inner_socket());
                if( pmq::detail::is_ssl_handshake(socket.get()) ){
                    return create_ssl_client_thread(socket,process);
                }
                auto f = std::bind(process,socket);
                return std::make_shared<std::thread>(f);




            }catch( const boost::system::system_error & e ){
                throw pmq::exception::acceptor_exception("Listening on port "
                                                         + std::to_string(config.get_port())
                                                         + " not established -"
                                                         + std::to_string(e.code().value())
                                                         + " - Error message : "
                                                         + e.what());
            }

        }
        [[nodiscard]] std::string get_password() const{
            return config.get_passphrase();
        }
    private:
        std::shared_ptr<std::thread> create_ssl_client_thread(const std::shared_ptr<pmq::socket> &socket,  std::function< void(std::shared_ptr<pmq::socket>&)> & process) {
            try {
                auto * ssl_socket = new ::ssl_socket(std::move(*(socket->get_inner_socket())), ssl_contex);

                std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(ssl_socket);


                boost::system::error_code  ec;

                ssl_socket->handshake(boost::asio::ssl::stream_base::server,ec);
                if(ec.value() != boost::system::errc::success){
                    std::cout<<std::to_string(ec.value())<<std::endl;
                    std::cout<<ec.message()<<std::endl;
                    throw pmq::exception::tls_handshake_exception("TLS handshake error - Code :"
                                                                  + std::to_string(ec.value())
                                                                  + " - Error message : "
                                                                  + ec.message() );
                }
                BOOST_LOG_TRIVIAL(debug)<<"Received client certificate name:"<<socket->get_normalized_subject_name()<<std::endl;
                s_socket->set_subject_name(socket->get_subject_name());
                auto f = std::bind(process, s_socket);
                return std::make_shared<std::thread>(f);
            }catch( const boost::system::system_error & e ){
                throw pmq::exception::acceptor_exception("Listening on port "
                                                         + std::to_string(config.get_port())
                                                         + " not established -"
                                                         + std::to_string(e.code().value())
                                                         + " - Error message : "
                                                         + e.what());
            }
        }
    private:
        boost::asio::io_context context;
        boost::asio::ssl::context ssl_contex;

        pmq::config config;
    };
}

#endif //PMQ_CONNECTION_FACTORY_HPP
