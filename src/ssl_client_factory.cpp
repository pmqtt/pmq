//
// Created by pmqtt on 2019-06-23.
//
#include <boost/asio/ssl.hpp>
#include "header/ssl_client_factory.hpp"


namespace pmq{
    ssl_client_factory::ssl_client_factory(boost::asio::io_context &context, std::size_t port)
        : context(context),
          port(port),
          ssl_contex(boost::asio::ssl::context::sslv23){

        ssl_contex.set_options(
                boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
        );//| boost::asio::ssl::context::single_dh_use);
        ssl_contex.set_password_callback(boost::bind(&ssl_client_factory::get_password,this));
        ssl_contex.use_certificate_chain_file("/Users/cefour/Projects/cert/server.crt");
        //ssl_contex.use_certificate_file("/Users/cefour/Projects/test_cert/client.crt",boost::asio::ssl::context::pem);
        ssl_contex.use_private_key_file("/Users/cefour/Projects/cert/server.key",boost::asio::ssl::context::pem);
        ssl_contex.use_tmp_dh_file("/Users/cefour/Projects/cert/dh2048.pem");

        //ssl_contex.set_verify_mode(boost::asio::ssl::context::verify_fail_if_no_peer_cert | boost::asio::ssl::context::verify_peer);
        //ssl_contex.load_verify_file("/Users/cefour/Projects/test_cert/ca.crt");
        //ssl_contex.add_certificate_authority("/Users/cefour/Projects/test_cert/ca.crt");
        //ssl_contex.use_certificate_chain_file("/Users/cefour/Projects/test_cert/user/user.crt");
        //ssl_contex.use_private_key_file("/Users/cefour/Projects/test_cert/server.key",boost::asio::ssl::context::pem);
        //ssl_contex.use_tmp_dh_file("/Users/cefour/Projects/test_cert/dh2048.pem");
        //ssl_contex.use_
    }
    ssl_client_factory::~ssl_client_factory() {

    }
    std::string ssl_client_factory::get_password()const {
        return "82517";
    }


    std::shared_ptr<boost::thread> ssl_client_factory::create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) {
        try {
            std::cout<<"create socket"<<std::endl;

            ssl_socket *socket = new ssl_socket(context, ssl_contex);
            tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), this->port));
            acceptor.accept(socket->lowest_layer());
            std::cout<<"socket->handshake()"<<std::endl;
            boost::system::error_code  ec;
            socket->handshake(boost::asio::ssl::stream_base::server,ec);
            std::cout<<"error_code:"<<ec.message()<<std::endl;
            std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(socket);
            auto f = std::bind(process, s_socket);
            return std::make_shared<boost::thread>(f);
        }catch(...){
            std::cout<<"FOO BAR";
        }
    }
}
