//
// Created by pmq on 02.01.20.
//

#ifndef PMQ_TLS_CERTIFICATE_HPP
#define PMQ_TLS_CERTIFICATE_HPP
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <openssl/crypto.h>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>


namespace pmq{
    namespace detail{

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
}

#endif //PMQ_TLS_CERTIFICATE_HPP
