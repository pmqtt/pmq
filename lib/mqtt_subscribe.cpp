//
// Created by Michael Burzan on 2019-03-31.
//
#include "lib/mqtt_package.hpp"
#include "lib/mqtt_subscribe.hpp"
#include "socket.hpp"



pmq::mqtt_subscribe::mqtt_subscribe(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length)
        :pmq::mqtt_package(client_socket),payload_length(payload_length){

}

void pmq::mqtt_subscribe::parse(const std::string & payload) {
    std::size_t current_byte_index = 0;

    this->msg_id = this->calculate_index_from_msb_lsb(payload[0],payload[1]);
    this->msg_msb = payload[0];
    this->msg_lsb = payload[1];
    current_byte_index += 2;
    while((payload_length - current_byte_index) > 0){
        this->topic = this->read_string(payload,current_byte_index);
        this->topic_qos = payload[current_byte_index++];
        BOOST_LOG_TRIVIAL(debug)<<"[pmq::mqtt_subscribe::parse] \{"
                                <<"\t\n msg id          : " << this->msg_id
                                <<"\t\n topic           : " << topic
                                <<"\t\n qos             : " << topic_qos
                                <<"\t\n payload length  : " <<payload.length()
                                <<"\t\n current_b_index : " << current_byte_index
                                <<"\n}";

        this->topic_container.push_back({topic_qos,topic});
    }
}

void pmq::mqtt_subscribe::accept(pmq::mqtt_visitor &v) {
    v.visit(this);
}