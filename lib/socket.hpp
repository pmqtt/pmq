//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_SOCKET_HPP
#define PMQ_SOCKET_HPP
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <thread>
#include <vector>


#include "socket_functions.hpp"
#include "header/exception/socket_exception.hpp"

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
        socket() : inner_socket(nullptr) {}
        socket(const socket & rhs)= delete;

        explicit socket(boost::asio::ip::tcp::socket * sock)
            : inner_socket(sock) { }
        socket(socket && rhs) noexcept
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
        std::mutex mutex;
    };



}
#endif //PMQ_SOCKET_HPP
