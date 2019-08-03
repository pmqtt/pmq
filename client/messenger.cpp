//
// Created by pmqtt on 2019-07-28.
//


#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <lib/socket.hpp>

#include "messenger.hpp"

using boost::asio::ip::tcp;
pmq::client::messenger::messenger() {

}

pmq::client::messenger::~messenger() {

}

pmq::client::messenger &pmq::client::messenger::set_qos(const std::size_t qos) {
    return *this;
}

pmq::client::messenger &pmq::client::messenger::set_broker_address(const std::string &address, std::size_t port) {
    return *this;;
}

pmq::client::messenger &pmq::client::messenger::set_broker_address(const std::string &address) {
    return *this;;
}

pmq::client::messenger &pmq::client::messenger::set_keep_alive(std::size_t sec) {
    return *this;;
}

pmq::client::messenger &pmq::client::messenger::set_clean_session(bool clean) {
    return *this;;
}

void pmq::client::messenger::connect() {

}

void pmq::client::messenger::connect_infinity() {

}

void pmq::client::messenger::subscribe(const std::string &topic) {

}

void pmq::client::messenger::publish(const std::string &topic, const std::string &payload) {

}

std::pair<std::string, std::string> pmq::client::messenger::get_message() {
    return std::pair<std::string, std::string>();
}

void pmq::client::messenger::connect(const std::string & host,std::size_t port) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    tcp::socket socket(io_context);
    boost::asio::connect(socket, iterator);

}


