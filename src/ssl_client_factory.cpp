//
// Created by pmqtt on 2019-06-23.
//
#include <boost/asio/ssl.hpp>
#include "header/acceptor_exception.hpp"
#include "header/tls_handshake_exception.hpp"
#include "header/ssl_client_factory.hpp"


namespace pmq{
    ssl_client_factory::ssl_client_factory( const pmq::config & cfg)
        : config(cfg), ssl_contex(boost::asio::ssl::context::sslv23){


        ssl_contex.set_options(
                  boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
                | boost::asio::ssl::context::single_dh_use);

        ssl_contex.set_password_callback(boost::bind(&ssl_client_factory::get_password,this));
        ssl_contex.use_certificate_chain_file(cfg.get_tls_cert_path());
        ssl_contex.use_private_key_file(cfg.get_tls_private_key(),boost::asio::ssl::context::pem);
        ssl_contex.use_tmp_dh_file(cfg.get_tls_dh_file());

    }
    ssl_client_factory::~ssl_client_factory() {

    }
    std::string ssl_client_factory::get_password()const {
        return " ";
    }


    std::shared_ptr<boost::thread> ssl_client_factory::create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) {
        try {

            ssl_socket * socket = new ssl_socket(context, ssl_contex);
            std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(socket);

            tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), config.get_port() ) );
            acceptor.accept(socket->lowest_layer());
            boost::system::error_code  ec;
            socket->handshake(boost::asio::ssl::stream_base::server,ec);
            if(ec.value() != boost::system::errc::success){
                throw pmq::exception::tls_handshake_exception("TLS handshake error - Code :"
                                                              + std::to_string(ec.value())
                                                              + " - Error message : "
                                                              + ec.message() );
            }
            auto f = std::bind(process, s_socket);
            return std::make_shared<boost::thread>(f);
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
