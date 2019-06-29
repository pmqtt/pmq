//
// Created by pmqtt on 2019-06-29.
//
#include "header/client_handler.hpp"
#include "lib/subscriber.hpp"

namespace {
    typedef std::map<std::string,std::list<std::shared_ptr<pmq::socket>>> SubscriptionContainer;
    std::map<std::string,std::list<pmq::subscriber>> subscripted_clients;
    std::map<pmq::u_int16 , std::shared_ptr<pmq::mqtt_publish> > message_storage;
}



void pmq::client_handler::visit(pmq::mqtt_connect *msg) {

}

void pmq::client_handler::visit(pmq::mqtt_publish *msg) {
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

void pmq::client_handler::visit(pmq::mqtt_subscribe *msg) {
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

void pmq::client_handler::visit(pmq::mqtt_ping_request *msg) {
    BOOST_LOG_TRIVIAL(info)<<"SEND PING RESPONE";
    auto client_socket = msg->get_socket();
    pmq::mqtt_ping_response response(client_socket);
    response.send();
}



void pmq::client_handler::visit(pmq::mqtt_ping_response * msg) {

}

void pmq::client_handler::visit(pmq::mqtt_disconnect *msg) {

}

void pmq::client_handler::visit(pmq::mqtt_pubcomp *msg) {
    BOOST_LOG_TRIVIAL(info)<<"RECV: pubcomp";
}

void pmq::client_handler::visit(pmq::mqtt_pubrec *msg) {
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

void pmq::client_handler::visit(pmq::mqtt_pubrel *msg) {
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

void pmq::client_handler::visit(pmq::mqtt_connack *msg) {

}

void pmq::client_handler::visit(pmq::mqtt_unsuback *msg) {

}

void pmq::client_handler::visit(pmq::mqtt_suback *msg) {

}

void pmq::client_handler::visit(pmq::mqtt_puback *msg) {

}