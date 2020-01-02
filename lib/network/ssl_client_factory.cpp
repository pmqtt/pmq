//
// Created by pmqtt on 2019-06-23.
//
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <openssl/crypto.h>

#include <lib/exception/acceptor_exception.hpp>
#include <lib/exception/tls_handshake_exception.hpp>
#include "ssl_client_factory.hpp"



namespace pmq{
    /*
     * synchron ssl handling with boost::asio
     */
    ssl_client_factory::ssl_client_factory( const pmq::config & cfg)
        : config(cfg), ssl_contex(boost::asio::ssl::context::sslv23){

        try {
            ssl_contex.set_options(
                    boost::asio::ssl::context::default_workarounds
                    | boost::asio::ssl::context::no_sslv2
                    | boost::asio::ssl::context::single_dh_use);
            ssl_contex.set_verify_mode(boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);
            ssl_contex.set_password_callback(boost::bind(&ssl_client_factory::get_password, this));
            ssl_contex.use_certificate_chain_file(cfg.get_tls_cert_path());

            ssl_contex.use_private_key_file(cfg.get_tls_private_key(), boost::asio::ssl::context::pem);
            ssl_contex.use_tmp_dh_file(cfg.get_tls_dh_file());
        }catch( const boost::system::system_error & e ){
            throw pmq::exception::config_exception(e.what());
        }
    }
    ssl_client_factory::~ssl_client_factory() = default;
    std::string ssl_client_factory::get_password()const {
        return config.get_passphrase();
    }


    std::shared_ptr<std::thread> ssl_client_factory::create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) {
        try {

            ssl_socket * socket = new ssl_socket(context, ssl_contex);
            std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(socket);
            tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), config.get_port() ) );
            acceptor.accept(socket->lowest_layer());
            if(!pmq::detail::is_ssl_handshake(s_socket.get())){
                throw pmq::exception::socket_exception("Plain socket connection detected but only tls socket configured");
            }
            boost::system::error_code  ec;

            socket->handshake(boost::asio::ssl::stream_base::server,ec);
            auto verify_certificate_cb = [&](bool preverified, boost::asio::ssl::verify_context& ctx)->bool{
                return s_socket->verify_certificate(preverified,ctx);
            };


            ssl_contex.set_verify_callback(verify_certificate_cb);

            if(ec.value() != boost::system::errc::success){
                std::cout<<std::to_string(ec.value())<<std::endl;
                std::cout<<ec.message()<<std::endl;
                throw pmq::exception::tls_handshake_exception("TLS handshake error - Code :"
                                                              + std::to_string(ec.value())
                                                              + " - Error message : "
                                                              + ec.message() );
            }
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
}
