//
// Created by PMQTT on 2019-03-30.
//
#include "control_packet_type.hpp"
#include "mqtt_package.hpp"
#include "mqtt_publish.hpp"
#include "mqtt_message_processor.hpp"
#include "lib/network/socket.hpp"

pmq::mqtt_publish::mqtt_publish(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length,pmq::u_int8 header)
        :pmq::mqtt_package(client_socket),payload_length(payload_length),header(header){
    BOOST_LOG_TRIVIAL(debug)<<"[publish] rl "<<(std::size_t)payload_length;
}



void pmq::mqtt_publish::parse(const std::string & payload) {
    BOOST_LOG_TRIVIAL(debug)<<"PRINTED HEADER:"<<(int)header;
    this->dup    = (this->header & 0x08)>>3;
    this->qos    = (this->header & 0x06)>>1;
    this->retain = (this->header & 0x01);

    std::size_t current_index = 0;
    this->topic = read_string(payload,current_index);
    if(this->qos > 0) {
        this->message_id = payload.substr(current_index,2);
        this->message_id_as_int = this->calculate_index_from_msb_lsb(this->message_id[0],this->message_id[1]);
        current_index += 2;
    }
    this->message = payload.substr(current_index);
    BOOST_LOG_TRIVIAL(debug) <<"[pmq::mqtt_publish::parse] \n{"
                             <<"\n\t dup     : "<< dup
                             <<"\n\t qos     : "<< qos
                             <<"\n\t retain  : "<< retain
                             <<"\n\t topic   : "<< topic
                             <<"\n\t message : "<< message
                             <<"\n}";

}

void pmq::mqtt_publish::accept(pmq::mqtt_visitor &v) {
    v.visit(this);
}

void pmq::mqtt_publish::send(std::shared_ptr<pmq::socket> & socket)const{
    std::string msg;
    pmq::u_int8 first_byte = pmq::CONTROL_PACKET_TYPE::PUBLISH <<4;
    std::string topic_length = detail::encode(topic.length());
    std::string remaining_length = detail::encode(1+topic_length.length()+
            this->message.length()+
            this->topic.length());
    pmq::u_int8 variable_header = 0;
    msg += first_byte;
    msg += remaining_length;
    msg += variable_header;
    msg += topic_length;
    msg += topic;
    msg += message;
    BOOST_LOG_TRIVIAL(debug)<<"msg: "<<message <<" | "<<" topic: "<<topic;
    socket->write(msg);

}

const std::string &pmq::mqtt_publish::get_client_id() const {
    return client_id;
}

void pmq::mqtt_publish::set_client_id(const std::string &clientId) {
    client_id = clientId;
}
