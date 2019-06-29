//
// Created by PMQTT on 2019-03-30.
//
#include "lib/mqtt_package.hpp"
#include "lib/mqtt_connect.hpp"
#include "lib/mqtt_types.hpp"
#include "pmqtt.hpp"
#include "socket.hpp"


pmq::mqtt_connect::mqtt_connect(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length)
    : pmq::mqtt_package(client_socket), payload_length(payload_length){

}


void pmq::mqtt_connect::parse(const std::string &payload) {
    std::size_t expected_payload_length = 10;
    if(payload.length() < expected_payload_length){
        //Todo Create Exception
        BOOST_LOG_TRIVIAL(debug)<<"[void pmq::mqtt_connect::parse] payload length has not the expected value\n{"
                                <<"\t\n expected_payload_length : " <<expected_payload_length
                                <<"\t\n payload.length          : " <<payload.length()
                                <<"\n}";
        return;
    }
    BOOST_LOG_TRIVIAL(info)<<"void pmq::mqtt_connect::parse] payload length: "<<payload.length();
    std::size_t current_byte_index = 0;
    std::string mqtt_string = this->read_string(payload,current_byte_index);
    this->version = static_cast<unsigned int>( payload[current_byte_index++] );
    this->api = pmq::mqtt_api_factory(mqtt_string,this->version);



    pmq::u_int8 connection_flags = payload[current_byte_index++];

    this->reserved       = connection_flags & 1;
    this->clean_start    = (connection_flags >>1)  &1;
    this->will_flag      = (connection_flags >>2)  &1;
    this->will_qos       = static_cast<unsigned  int>((connection_flags >>3)  &3);
    this->will_retain    = (connection_flags >>5)  &1;
    this->password_flag  = (connection_flags >> 6) &1;
    this->user_name_flag = (connection_flags >> 7) &1;
    this->keep_alive     = this->calculate_index_from_msb_lsb(payload[current_byte_index+1],payload[current_byte_index+2]);
    current_byte_index += 2;



    if(this->version == 5) {
        int sLength = (int) payload[current_byte_index];
        BOOST_LOG_TRIVIAL(info) << "Readed length : " << sLength;
    }
    this->client_id = this->read_string(payload,current_byte_index);

    if(this->will_flag){
        this->will_topic = this->read_string(payload,current_byte_index);
        this->will_payload = this->read_string(payload,current_byte_index);

    }
    if(this->user_name_flag){
        this->user_name = this->read_string(payload,current_byte_index);
    }
    if(this->password_flag){
        this->password = this->read_string(payload,current_byte_index);
    }
    BOOST_LOG_TRIVIAL(debug) <<"[void pmq::mqtt_connect::parse] CONNECT HEADER\n{"
                             << "\n\t version        : " << this->version
                             << "\n\t reserved       : " << this->reserved
                             << "\n\t clean start    : " << this->clean_start
                             << "\n\t will flag      : " << this->will_flag
                             << "\n\t will qos       : " << this->will_qos
                             << "\n\t will retain    : " << this->will_retain
                             << "\n\t password flag  : " << this->password_flag
                             << "\n\t user name flag : " << this->user_name_flag
                             << "\n\t keep alive msb : " << this->keep_alive
                             << "\n\t client id      : " << this->client_id
                             << "\n\t will topic     : " << this->will_topic
                             << "\n\t will payload   : " << this->will_payload
                             << "\n\t user name      : " << this->user_name
                             << "\n\t password       : " << this->password
                             << "\n\t payload length : " << payload.length()
                             << "\n\t currentb_index : " << current_byte_index
                             << "\n\t rest_length    : " << payload.length()-current_byte_index
                             <<"\n}";

}

void pmq::mqtt_connect::accept(pmq::mqtt_visitor &v) {
    v.visit(this);
}

