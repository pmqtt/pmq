//
// Created by Michael Burzan on 2019-03-31.
//

#ifndef PMQ_MQTT_STATIC_PACKAGE_HPP
#define PMQ_MQTT_STATIC_PACKAGE_HPP

#include "mqtt_package.hpp"
#include "mqtt_types.hpp"
namespace pmq{
    template <pmq::u_int8 HEADER,pmq::u_int8 PAYLOAD_LENGTH>
    class mqtt_static_package : public mqtt_package{
    public:
        mqtt_static_package(std::shared_ptr<pmq::socket> & client_socket)
                :mqtt_package(client_socket){

        }
        virtual ~mqtt_static_package(){}

        std::size_t get_payload_length() const override {
            return PAYLOAD_LENGTH;
        }
        void send() override{
            std::string send_msg;
            send_msg += HEADER;
            send_msg += PAYLOAD_LENGTH;
            client_socket->write(send_msg);
        }
        void parse(const std::string & payload) override{

        }
        void accept(mqtt_visitor & v) override {
            v.visit(this);
        }
    };

    template <pmq::u_int8 HEADER,pmq::u_int8 PAYLOAD_LENGTH>
    class mqtt_controll_package : public mqtt_package{
    public:
        mqtt_controll_package(std::shared_ptr<pmq::socket> & client_socket,pmq::u_int8 msb,pmq::u_int8 lsb)
                :mqtt_package(client_socket),msb(msb),lsb(lsb){

        }
        mqtt_controll_package( std::shared_ptr<pmq::socket> & client_socket)
                :mqtt_package(client_socket){

        }
        virtual ~mqtt_controll_package(){}

        std::size_t get_payload_length() const override {
            return PAYLOAD_LENGTH;
        }
        void send() override{
            std::string send_msg;
            send_msg += HEADER;
            send_msg += PAYLOAD_LENGTH;
            send_msg += this->msb;
            send_msg += this->lsb;
            client_socket->write(send_msg);
        }
        void send(const std::string &message_id){
            std::string send_msg;
            send_msg += HEADER;
            send_msg += PAYLOAD_LENGTH;
            send_msg += message_id;
            client_socket->write(send_msg);
        }

        void parse(const std::string & payload) override{
            msb = payload[0];
            lsb = payload[1];
        }
        void accept(mqtt_visitor & v) override {
            v.visit(this);
        }
        pmq::u_int8 get_msb()const{
            return msb;
        }
        pmq::u_int8 get_lsb()const{
            return lsb;
        }
        pmq::u_int16 get_message_id()const{
            return this->calculate_index_from_msb_lsb(msb,lsb);
        }

    private:
        pmq::u_int8 msb;
        pmq::u_int8 lsb;
    };

    typedef mqtt_static_package<192,0> mqtt_ping_request;
    typedef mqtt_static_package<208,0> mqtt_ping_response;
    typedef mqtt_static_package<224,0> mqtt_disconnect;
    typedef mqtt_controll_package<112,2> mqtt_pubcomp;
    typedef mqtt_controll_package<80,2> mqtt_pubrec;
    typedef mqtt_controll_package<98,2> mqtt_pubrel;
    typedef mqtt_controll_package<32,2> mqtt_connack;
    typedef mqtt_controll_package<176,2> mqtt_unsuback;
    typedef mqtt_controll_package<144,2> mqtt_suback;
    typedef mqtt_controll_package<64,2> mqtt_puback;

}

#endif //PMQ_MQTT_STATIC_PACKAGE_HPP
