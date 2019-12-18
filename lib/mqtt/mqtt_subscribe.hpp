//
// Created by PMQTT on 2019-03-31.
//

#ifndef PMQ_MQTT_SUBSCRIBE_HPP
#define PMQ_MQTT_SUBSCRIBE_HPP

#include <tuple>
#include <vector>

namespace pmq {
    class mqtt_package;
    class mqtt_subscribe : public mqtt_package {
    public:
        mqtt_subscribe(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length);
        virtual ~mqtt_subscribe(){}

        [[nodiscard]] std::size_t get_payload_length() const override {
            return this->payload_length;
        }
        void parse(const std::string & payload) override ;
        void accept(mqtt_visitor & v) override;

        [[nodiscard]] const std::string & get_topic()const{
            return this->topic;
        }
        pmq::u_int16  get_qos(){
            return this->topic_qos;
        }
        [[nodiscard]] pmq::u_int16 get_msg_id()const{
            return this->msg_id;
        }
        [[nodiscard]] constexpr pmq::u_int8 get_msg_msb()const{
            return this->msg_msb;
        }
        [[nodiscard]] constexpr pmq::u_int8 get_msg_lsb()const{
            return this->msg_lsb;
        }

    private:
        std::string topic;
        pmq::u_int16  topic_qos;
        std::vector<std::tuple<pmq::u_int16,std::string>> topic_container;
    private:
        std::size_t payload_length;
        pmq::u_int16 msg_id;
        pmq::u_int8 msg_msb;
        pmq::u_int8 msg_lsb;

    };

}


#endif //PMQ_MQTT_SUBSCRIBE_HPP
