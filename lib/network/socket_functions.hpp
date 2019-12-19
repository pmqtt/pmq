//
// Created by PMQTT on 2019-07-06.
//

#ifndef PMQ_SOCKET_FUNCTIONS_HPP
#define PMQ_SOCKET_FUNCTIONS_HPP


#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <string>

#include <lib/exception/socket_exception.hpp>
#include <sys/socket.h>


namespace pmq{
    namespace detail{

        template<class SOCKET>
        bool is_ssl_handshake(SOCKET * inner_socket){
            auto native_socket = inner_socket->get_inner_socket()->native_handle();
            char buffer;
            ::recv(native_socket,&buffer,1,MSG_PEEK);
            return buffer == 0x16;
        }

        template<class SOCKET>
        std::string read(SOCKET * inner_socket,std::size_t size){
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

        template<class SOCKET>
        void write(SOCKET * inner_socket,std::mutex & mutex,const std::string & msg){
            std::unique_lock<std::mutex> lock(mutex);
            boost::system::error_code ignored_error;
            std::size_t x = boost::asio::write(*inner_socket,boost::asio::buffer(msg),ignored_error);

        }
    }
}

#endif //PMQ_SOCKET_FUNCTIONS_HPP
