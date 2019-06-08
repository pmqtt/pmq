//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_SOCKET_HPP
#define PMQ_SOCKET_HPP
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>

#include "header/socket_exception.hpp"

using boost::asio::ip::tcp;

namespace pmq{

    class socket{
    public:
        std::string read(std::size_t size){
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


        void write(const std::string & msg){
            boost::unique_lock<boost::mutex> lock(mutex);
            boost::system::error_code ignored_error;
            std::size_t x = boost::asio::write(*inner_socket,boost::asio::buffer(msg),ignored_error);
            BOOST_LOG_TRIVIAL(debug)<<"Sended: "<< x << " | "<<msg.length()<< " | " << ignored_error.message();
        }

        std::string_view get_address()const{
            return this->inner_socket->local_endpoint().address().to_string();
        }
        void close(){
            if(this->is_connected())
                this->inner_socket->close();
        }
        bool is_connected() const{
            return this->inner_socket->is_open();
        }
    public:
        socket() = delete;
        socket(const socket & rhs)= delete;
        socket(tcp::socket * sock)
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
        }
    private:
        tcp::socket* inner_socket;
        boost::mutex mutex;
    };
}
#endif //PMQ_SOCKET_HPP
