//
// Created by pmqtt on 2019-06-23.
//
#include <boost/asio/ssl.hpp>
#include "header/ssl_client_factory.hpp"


namespace pmq{
    ssl_client_factory::ssl_client_factory( std::size_t port,const pmq::config & cfg)
        : port(port),
          ssl_contex(boost::asio::ssl::context::sslv23){

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

            ssl_socket *socket = new ssl_socket(context, ssl_contex);
            tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), this->port));
            acceptor.accept(socket->lowest_layer());
            boost::system::error_code  ec;
            socket->handshake(boost::asio::ssl::stream_base::server,ec);
            std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(socket);
            auto f = std::bind(process, s_socket);
            return std::make_shared<boost::thread>(f);
        }catch(...){
            //TODO CAPTURE EXCEPTION
        }
    }
}
