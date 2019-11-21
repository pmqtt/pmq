//
// Created by pmqtt on 2019-06-29.
//
#include "header/client_handler.hpp"
#include "lib/message.hpp"
#include "lib/mqtt_connect.hpp"
#include "lib/subscriber.hpp"


void pmq::client_handler::visit(pmq::mqtt_connect *msg) {
    BOOST_LOG_TRIVIAL(debug)<<"Handle connection";
    login_creator->create(config.is_allow_anonymous_login())->handle(storage_service,msg);
    std::shared_ptr<pmq::mqtt_connect> client_connection(msg,[](pmq::mqtt_connect* p){ });
    storage_service->add_client(client_connection);
    this->client_id = msg->get_client_id();
    auto socket = msg->get_socket();
    pmq::mqtt_connack connack( socket,0x0, 0x0);
    connack.send();
}

void pmq::client_handler::visit(pmq::mqtt_publish *msg) {
    BOOST_LOG_TRIVIAL(debug) << "[visit publish] ";
    msg->set_client_id(client_id);
    qos_factory->create(msg->get_qos())->handle(storage_service,msg);
    if(msg->is_retained()){
        std::shared_ptr<pmq::message> message = std::make_shared<pmq::message>(msg->get_topic(),
                msg->get_message(),pmq::create_qos_from_int(msg->get_qos()));
        //storage_service->add_retained_message(message);
    }
    const std::string topic = msg->get_topic();
    for( const auto & subscriber : storage_service->get_subscriber(topic)) {
        *subscriber << msg->get_message();
    }

}

void pmq::client_handler::visit(pmq::mqtt_subscribe *msg) {
    const std::string topic = msg->get_topic();
    auto socket = msg->get_socket();
    BOOST_LOG_TRIVIAL(debug)<<"SUBSCRIBED WITH QOS:"<<msg->get_qos();
    std::shared_ptr<pmq::subscriber> subscriber = std::make_shared<pmq::subscriber>(socket,topic,msg->get_qos());
    storage_service->add_subscriber(topic,subscriber);
    pmq::mqtt_suback suback(socket,msg->get_msg_msb(),msg->get_msg_lsb(),2);
    suback.send();
    std::vector<std::shared_ptr<pmq::message>> retained_messages = storage_service->get_retained_messages();
    for(const auto & x : retained_messages){
        std::vector<std::shared_ptr<pmq::subscriber>> subscribers = storage_service->get_subscriber(x->get_topic());
        for( auto & sub : subscribers){
            if(sub.get() == subscriber.get()){
                *subscriber<<x->get_payload();
            }
        }
    }



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
    BOOST_LOG_TRIVIAL(info)<<"RECV: disconnect";
    msg->get_socket()->close();
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
    try {
        std::string mid = storage_service->restore_qos_two_publish_msg(this->client_id);
        auto client_socket = msg->get_socket();
        pmq::mqtt_pubcomp pubcomp(client_socket);
        pubcomp.send(mid);
    }catch(std::exception & e){
        BOOST_LOG_TRIVIAL(error)<<e.what();
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

void pmq::client_handler::handleDisconnect() {
    pmq::message msg = storage_service->get_will_message(client_id);
    auto subscribers = storage_service->get_subscriber(msg.get_topic());
    for(const auto & subscriber : subscribers){
        std::string will_msg = msg.get_payload();
        BOOST_LOG_TRIVIAL(debug)<< "WILL PAYLOAD:"<< will_msg;
        *subscriber<<will_msg;
    }
    storage_service->remove_client(client_id);
}