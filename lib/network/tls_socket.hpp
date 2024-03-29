//
// Created by pmqtt on 2019-07-03.
//

#ifndef PMQ_TLS_SOCKET_HPP
#define PMQ_TLS_SOCKET_HPP
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include <lib/exception/socket_exception.hpp>
#include "socket_functions.hpp"
#include "socket.hpp"

namespace pmq {

    class tls_socket : public socket {
    public:
        std::string read(std::size_t size) override {
            return pmq::detail::read<ssl_socket>(inner_socket,size);
        }


        void write(const std::string &msg) override {
           pmq::detail::write<ssl_socket>(inner_socket,mutex,msg);
        }

        [[nodiscard]] std::string get_address() const override {
            return this->inner_socket->lowest_layer().local_endpoint().address().to_string();
        }

        void close() override {
            if (this->is_connected())
                this->inner_socket->lowest_layer().close();
        }

        bool is_connected() const override {
            return this->inner_socket->lowest_layer().is_open();
        }

    public:
        tls_socket() = delete;

        tls_socket(const tls_socket &rhs) = delete;

        explicit tls_socket(ssl_socket *sock)
                : inner_socket(sock) {}

        tls_socket(tls_socket &&rhs)
                : inner_socket(std::move(rhs.inner_socket)) {}

        tls_socket &operator=(tls_socket &&rhs) {
            this->inner_socket = std::move(rhs.inner_socket);
            return *this;
        }

        ~tls_socket() override {
            if (inner_socket->lowest_layer().is_open()) {
                this->inner_socket->lowest_layer().close();
            }
            delete this->inner_socket;
        }

        ssl_socket *get_inner_socket() {
            return inner_socket;
        }

    private:
        ssl_socket *inner_socket;
        std::mutex mutex;
    };
}
#endif //PMQ_TLS_SOCKET_HPP
