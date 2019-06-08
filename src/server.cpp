//
// Created by Michael Burzan on 2019-03-03.
//

#include "lib/mqtt_static_package.hpp"
#include "lib/subscriber.hpp"
#include "header/server.hpp"

#include <list>
#include <map>
#include <string>

namespace {
    typedef std::map<std::string,std::list<std::shared_ptr<pmq::socket>>> SubscriptionContainer;
    std::map<std::string,std::list<pmq::subscriber>> subscripted_clients;
    std::map<pmq::u_int16 , std::shared_ptr<pmq::mqtt_publish> > message_storage;
}


pmq::server::~server() {

}

void pmq::server::run(){
    while(this->should_service_run){
        tcp::socket *socket = new tcp::socket(this->io_context);
        this->acceptor.accept(*socket);
        auto process_func = std::bind(&server::process,this,
                                      std::make_shared<pmq::socket>(socket));
        this->client_threads.emplace_back( std::make_shared<boost::thread>(process_func) );
    }
    clean_up();
}


void pmq::server::process(std::shared_ptr<pmq::socket> & socket) {
    try {
        auto client_info = this->server_info->add_new_client_info();
        client_info->connection_info->connection_socket = socket;

        pmq::mqtt_message message(socket);

        std::shared_ptr<pmq::mqtt_package> package = message.create_package(client_info->connection_info);

        pmq::mqtt_connack connack(socket, 0x0, 0x0);
        connack.send();
        while (socket->is_connected()) {
            std::shared_ptr<pmq::mqtt_package> action_package = message.create_package(client_info->connection_info);
            action_package->accept(*this);
        }
    } catch (pmq::exception::socket_exception &e) {
        BOOST_LOG_TRIVIAL(info) << "Client closed the connection";
    }
}

void pmq::server::clean_up() {

}

void pmq::server::visit(pmq::mqtt_connect *msg) {

}

void pmq::server::visit(pmq::mqtt_publish *msg) {
    BOOST_LOG_TRIVIAL(debug) << "[visit publish] ";
    switch (msg->get_qos()){
        case pmq::QOS::QOS_0 :
            break;
        case pmq::QOS::QOS_1: {
                    auto socket = msg->get_socket();
                    pmq::mqtt_puback ack(socket);
                    ack.send(msg->get_message_id());
                }
                break;
        case pmq::QOS::QOS_2: {
                   std::shared_ptr<pmq::mqtt_publish> msg_shared(msg);
                   message_storage[msg->get_message_id_as_int()] = msg_shared;
                   auto socket = msg->get_socket();

                   pmq::mqtt_pubrec pubrec(socket);
                   pubrec.send(msg->get_message_id());
               }
               break;
        default:
            break;
    }
    const std::string topic = msg->get_topic();
    if(subscripted_clients.count(topic) > 0){
        for( auto subscriber : subscripted_clients[topic]){
            subscriber << msg->get_message();

        }
    }

}

void pmq::server::visit(pmq::mqtt_subscribe *msg) {
    const std::string topic = msg->get_topic();
    auto socket = msg->get_socket();
    BOOST_LOG_TRIVIAL(debug)<<"SUBSCRIBED WITH QOS:"<<msg->get_qos();
    pmq::subscriber subscriber(socket,topic,msg->get_qos());
    subscripted_clients[topic].emplace_back(subscriber);

    pmq::u_int8 header = 144;
    pmq::u_int8 length = 3;
    pmq::u_int8 return_code = 2;
    std::string send_msg;
    send_msg += header;
    send_msg += length;
    send_msg += msg->get_msg_msb();
    send_msg += msg->get_msg_lsb();
    send_msg += return_code;

    pmq::u_int16 msg_id = msg->get_msg_id();
    pmq::u_int8 msb = msg_id & 0xFF00 >> 8;
    pmq::u_int8 lsb = msg_id & 0xFF;

    socket->write(send_msg);
}

void pmq::server::visit(pmq::mqtt_ping_request *msg) {
    BOOST_LOG_TRIVIAL(info)<<"SEND PING RESPONE";
    auto client_socket = msg->get_socket();
    pmq::mqtt_ping_response response(client_socket);
    response.send();

}

void pmq::server::visit(pmq::mqtt_static_package<208, 0> *msg) {

}

void pmq::server::visit(pmq::mqtt_static_package<224, 0> *msg) {

}

void pmq::server::visit(pmq::mqtt_pubcomp *msg) {
    BOOST_LOG_TRIVIAL(info)<<"RECV: pubcomp";
}

void pmq::server::visit(pmq::mqtt_pubrec *msg) {
    BOOST_LOG_TRIVIAL(info)<<"RECEIVED PUBREC";
    auto sock = msg->get_socket();
    pmq::mqtt_pubrel pubrel(sock);
    pmq::u_int8 msb = msg->get_msb();
    pmq::u_int8 lsb = msg->get_lsb();
    std::string mid;
    mid += msb;
    mid += lsb;
    pubrel.send(mid);

}

void pmq::server::visit(pmq::mqtt_pubrel *msg) {
    BOOST_LOG_TRIVIAL(info)<<"RECEIVED PUBREL";
    pmq::u_int16 message_id = msg->get_message_id();
    if(message_storage.count(message_id) == 1 ){
        try {

            std::shared_ptr<mqtt_publish> pubMsg =  message_storage[message_id];
            std::string mid;
            mid += pubMsg->get_message_id();
            auto client_socket = msg->get_socket();
            pmq::mqtt_pubcomp pubcomp(client_socket);
            pubcomp.send(mid);

        }catch(std::exception & e){
            BOOST_LOG_TRIVIAL(error)<<e.what();
        }
    }

}

void pmq::server::visit(pmq::mqtt_controll_package<32, 2> *msg) {

}

void pmq::server::visit(pmq::mqtt_controll_package<176, 2> *msg) {

}

void pmq::server::visit(pmq::mqtt_controll_package<144, 2> *msg) {

}

void pmq::server::visit(pmq::mqtt_puback *msg) {

}
