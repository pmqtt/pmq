//
// Created by pmqtt on 2019-06-23.
//
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <openssl/crypto.h>

#include <lib/exception/acceptor_exception.hpp>
#include <lib/exception/tls_handshake_exception.hpp>
#include <lib/network/ssl_client_factory.hpp>

namespace {
    bool verify_certificate_cb(bool preverified, boost::asio::ssl::verify_context& ctx)
    {
        int8_t subject_name[256];
        X509_STORE_CTX *cts = ctx.native_handle();
        int32_t length = 0;
        X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        int32_t depth = X509_STORE_CTX_get_error_depth(cts);
        auto error = X509_STORE_CTX_get_error(cts);
        switch (error)
        {
            case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
                break;
            case X509_V_ERR_CERT_NOT_YET_VALID:
            case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
                break;
            case X509_V_ERR_CERT_HAS_EXPIRED:
            case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
                break;
            case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
                preverified = true;
                break;
            default:
                break;
        }
        const int32_t name_length = 256;
        X509_NAME_oneline(X509_get_subject_name(cert), reinterpret_cast<char*>(subject_name), name_length);
        std::cout<<"Subject name:" <<  subject_name <<std::endl;

        return preverified;
    }
}

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
            ssl_contex.set_verify_callback(&verify_certificate_cb);
            ssl_contex.set_password_callback(boost::bind(&ssl_client_factory::get_password, this));
            ssl_contex.use_certificate_chain_file(cfg.get_tls_cert_path());

            ssl_contex.use_private_key_file(cfg.get_tls_private_key(), boost::asio::ssl::context::pem);
            ssl_contex.use_tmp_dh_file(cfg.get_tls_dh_file());
        }catch( const boost::system::system_error & e ){
            throw pmq::exception::config_exception(e.what());
        }
    }
    ssl_client_factory::~ssl_client_factory() {

    }
    std::string ssl_client_factory::get_password()const {
        return config.get_passphrase();
    }


    std::shared_ptr<std::thread> ssl_client_factory::create_client_thread( std::function< void(std::shared_ptr<socket>&)> & process) {
        try {

            ssl_socket * socket = new ssl_socket(context, ssl_contex);
            std::shared_ptr<pmq::socket> s_socket = std::make_shared<pmq::tls_socket>(socket);

            tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), config.get_port() ) );
            acceptor.accept(socket->lowest_layer());
            boost::system::error_code  ec;

            socket->handshake(boost::asio::ssl::stream_base::server,ec);
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
