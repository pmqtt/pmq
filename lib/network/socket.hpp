//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_SOCKET_HPP
#define PMQ_SOCKET_HPP
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include <lib/exception/socket_exception.hpp>
#include "socket_functions.hpp"

using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;


namespace pmq{

    class socket{
    public:
        virtual std::string read(std::size_t size){
            return pmq::detail::read<boost::asio::ip::tcp::socket>(inner_socket,size);
        }


        virtual void write(const std::string & msg){
            pmq::detail::write<boost::asio::ip::tcp::socket>(inner_socket,mutex,msg);
        }

        [[nodiscard]] virtual std::string get_address()const{
            return this->inner_socket->local_endpoint().address().to_string();
        }
        virtual void close(){
            if(this->is_connected())
                this->inner_socket->close();
        }
        [[nodiscard]] virtual bool is_connected() const{
            return this->inner_socket->is_open();
        }

        std::string get_normalized_subject_name()const{
            if(subject.empty()) return subject;
            if(subject.length() < 5) return "";
            return subject.substr(4);
        }

        virtual std::string get_subject_name()const{
            return subject;
        }

        void set_subject_name(const std::string & subject_name){
            this->subject = subject_name;
        }


    public:
        socket() : inner_socket(nullptr),subject("") {}
        socket(const socket & rhs)= delete;

        explicit socket(boost::asio::ip::tcp::socket * sock)
            : inner_socket(sock) { }
        socket(socket && rhs) noexcept
            : inner_socket(std::move(rhs.inner_socket)), subject(std::move(rhs.subject)){}

        socket &operator=(socket && rhs){
            this->inner_socket = std::move(rhs.inner_socket);
            this->subject = std::move(rhs.subject);
            return *this;
        }
        virtual ~socket(){
            if(inner_socket->is_open()){
                this->inner_socket->close();
            }
            delete this->inner_socket;
        }

        boost::asio::ip::tcp::socket * get_inner_socket(){
            return inner_socket;
        }

        bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx) {
            char subject_name[256];
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
            X509_NAME_oneline(X509_get_subject_name(cert), subject_name, name_length);
            subject = subject_name;

            return preverified;
        }


    private:
        boost::asio::ip::tcp::socket * inner_socket;
        std::mutex mutex;
        std::string subject;
    };



}
#endif //PMQ_SOCKET_HPP
