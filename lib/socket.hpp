//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_SOCKET_HPP
#define PMQ_SOCKET_HPP
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>

#include "header/socket_exception.hpp"

using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

namespace {
    std::size_t read(boost::asio::ip::tcp::socket & socket,std::size_t size,boost::asio::streambuf &stream_buffer){
        return boost::asio::read(socket, stream_buffer,
                          boost::asio::transfer_exactly(size));
    }
    std::size_t read(ssl_socket & socket,std::size_t size,boost::asio::streambuf &stream_buffer){
        return boost::asio::read(socket, stream_buffer,
                                 boost::asio::transfer_exactly(size));
    }


}

namespace pmq{

    class socket{
    public:
        virtual std::string read(std::size_t size){
            try {
                boost::asio::streambuf stream_buffer;

                std::size_t x = boost::asio::read(*inner_socket, stream_buffer,
                                                  boost::asio::transfer_exactly(size));
                std::string res = {buffers_begin(stream_buffer.data()), buffers_begin(stream_buffer.data()) + x};
                stream_buffer.consume(x);
                if (x - size != 0)
                    throw pmq::exception::socket_exception("Not enoght data in socket stream");

                return res;
            }catch(boost::system::system_error & e){
                throw pmq::exception::socket_exception("socket is disconnected");
            }
        }


        virtual void write(const std::string & msg){
            boost::unique_lock<boost::mutex> lock(mutex);
            boost::system::error_code ignored_error;
            std::size_t x = boost::asio::write(*inner_socket,boost::asio::buffer(msg),ignored_error);
            BOOST_LOG_TRIVIAL(debug)<<"Sended: "<< x << " | "<<msg.length()<< " | " << ignored_error.message();
        }

        virtual std::string_view get_address()const{
            return this->inner_socket->local_endpoint().address().to_string();
        }
        virtual void close(){
            if(this->is_connected())
                this->inner_socket->close();
        }
        virtual bool is_connected() const{
            return this->inner_socket->is_open();
        }
    public:
        socket() {}
        socket(const socket & rhs)= delete;
        socket(boost::asio::ip::tcp::socket * sock)
            : inner_socket(sock) { }
        socket(socket && rhs)
            : inner_socket(std::move(rhs.inner_socket)){}

        socket &operator=(socket && rhs){
            this->inner_socket = std::move(rhs.inner_socket);
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

    private:
        boost::asio::ip::tcp::socket * inner_socket;
        boost::mutex mutex;
    };


    class tls_socket : public socket{
    public:
        virtual std::string read(std::size_t size){
            try {
                boost::asio::streambuf stream_buffer;

                std::size_t x = boost::asio::read(*inner_socket, stream_buffer,
                                                  boost::asio::transfer_exactly(size));
                std::string res = {buffers_begin(stream_buffer.data()), buffers_begin(stream_buffer.data()) + x};
                stream_buffer.consume(x);
                if (x - size != 0)
                    throw pmq::exception::socket_exception("Not enoght data in socket stream");

                return res;
            }catch(boost::system::system_error & e){
                throw pmq::exception::socket_exception("socket is disconnected");
            }
        }


        virtual void write(const std::string & msg){
            boost::unique_lock<boost::mutex> lock(mutex);
            boost::system::error_code ignored_error;
            std::size_t x = boost::asio::write(*inner_socket,boost::asio::buffer(msg),ignored_error);
            BOOST_LOG_TRIVIAL(debug)<<"Sended: "<< x << " | "<<msg.length()<< " | " << ignored_error.message();
        }

        virtual std::string_view get_address()const{
            return this->inner_socket->lowest_layer().local_endpoint().address().to_string();
        }
        virtual void close(){
            if(this->is_connected())
                this->inner_socket->lowest_layer().close();
        }
        virtual bool is_connected() const{
            return this->inner_socket->lowest_layer().is_open();
        }
    public:
        tls_socket() = delete;
        tls_socket(const tls_socket & rhs)= delete;
        tls_socket(ssl_socket * sock)
                : inner_socket(sock) { }
        tls_socket(tls_socket && rhs)
                : inner_socket(std::move(rhs.inner_socket)){}

        tls_socket &operator=(tls_socket && rhs){
            this->inner_socket = std::move(rhs.inner_socket);
            return *this;
        }
        virtual ~tls_socket(){
            if(inner_socket->lowest_layer().is_open()){
                this->inner_socket->lowest_layer().close();
            }
            delete this->inner_socket;
        }

        ssl_socket * get_inner_socket(){
            return inner_socket;
        }

    private:
        ssl_socket * inner_socket;
        boost::mutex mutex;
    };

}
#endif //PMQ_SOCKET_HPP
