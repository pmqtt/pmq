//
// Created by PMQTT on 2019-03-28.
//

#include "lib/mqtt_package.hpp"
#include "lib/control_packet_type.hpp"
#include "lib/mqtt_bad_header_exception.hpp"
#include "lib/mqtt_connect.hpp"
#include "lib/mqtt_connection_info.hpp"
#include "lib/mqtt_exception.hpp"
#include "lib/mqtt_message.hpp"
#include "lib/mqtt_message_processor.hpp"

#include "lib/mqtt_publish.hpp"
#include "lib/mqtt_subscribe.hpp"
#include "lib/mqtt_types.hpp"
#include "lib/mqtt_static_package.hpp"




std::shared_ptr<pmq::mqtt_package> pmq::mqtt_message::create_package( std::shared_ptr<pmq::mqtt_connection_info> & connection_info){
    BOOST_LOG_TRIVIAL(debug)<<"[std::shared_ptr<pmq::mqtt_package> pmq::mqtt_message::create_package] read";
    std::string msg = this->client_socket->read(1);
    pmq::u_int8 first_byte   = msg[0];
    unsigned int msg_length  = detail::read_length(this->client_socket);

    first_byte = first_byte >> 4;

    switch(first_byte) {
        case pmq::CONTROL_PACKET_TYPE::CONNECT: {
            auto connect_message = std::make_shared<pmq::mqtt_connect>(this->client_socket,msg_length);
            std::string payload = this->client_socket->read(msg_length);
            connect_message->parse(payload);
            connection_info->client_id = connect_message->get_client_id();
            return connect_message;
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::CONNACK: {

        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PUBLISH: {


            auto publish_message = std::make_shared<pmq::mqtt_publish>(this->client_socket,msg_length,msg[0]);
            std::string payload = this->client_socket->read(msg_length);

            publish_message->parse(payload);
            return publish_message;
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PUBACK: {
            std::string payload = this->client_socket->read(msg_length);
            BOOST_LOG_TRIVIAL(debug)<<"PUB_ACK: "<<(std::size_t)payload[0] << " | " << ( std::size_t) payload[1];
            return std::make_shared<pmq::mqtt_puback>(this->client_socket,payload[0],payload[1]);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PUBREC: {

            std::string payload = this->client_socket->read(msg_length);
            BOOST_LOG_TRIVIAL(debug)<<"PUB_REC: "<<(std::size_t)payload[0] << " | " << ( std::size_t) payload[1];


            return std::make_shared<pmq::mqtt_pubrec>(this->client_socket,payload[0],payload[1]);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PUBREL: {

            std::string payload = this->client_socket->read(msg_length);
            BOOST_LOG_TRIVIAL(debug)<<"PUB_REL: "<<(std::size_t)payload[0] << " | " << ( std::size_t) payload[1] ;
            return std::make_shared<pmq::mqtt_pubrel>(this->client_socket,payload[0],payload[1]);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PUBCOMP: {
            std::string payload = this->client_socket->read(msg_length);
            BOOST_LOG_TRIVIAL(debug)<<"PUB_COMP: "<<(std::size_t)payload[0] << " | " << ( std::size_t) payload[1];
            return std::make_shared<pmq::mqtt_pubcomp>(this->client_socket,payload[0],payload[1]);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::SUBSCRIBE: {
            auto subscribe_message = std::make_shared<pmq::mqtt_subscribe>(this->client_socket,msg_length);
            std::string payload = this->client_socket->read(msg_length);
            subscribe_message->parse(payload);
            return subscribe_message;
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::SUBACK: {

        }
        break;
        case pmq::CONTROL_PACKET_TYPE::UNSUBSCRIPE: {

        }
        break;
        case pmq::CONTROL_PACKET_TYPE::UNSUBACK: {

        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PINGRQ: {
            return std::make_shared<pmq::mqtt_ping_request>(this->client_socket);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::PINGRESP: {
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::DISCONNECT: {
            BOOST_LOG_TRIVIAL(debug)<<"Disconnect client : " << connection_info->client_id;
            this->client_socket->close();
            return std::make_shared<pmq::mqtt_disconnect>(this->client_socket);
        }
        break;
        case pmq::CONTROL_PACKET_TYPE::AUTH: {

        }
        break;
    }
    throw pmq::exception::mqtt_bad_header_exception("Bad header number" + std::to_string(first_byte));

}
