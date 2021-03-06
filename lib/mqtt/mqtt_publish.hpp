//
// Created by PMQTT on 2019-03-30.
//

#ifndef PMQ_MQTT_PUBLISH_HPP
#define PMQ_MQTT_PUBLISH_HPP

namespace pmq {
    class mqtt_package;
    class socket;
    class mqtt_publish : public mqtt_package{
    public:
        mqtt_publish(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length, pmq::u_int8 header);
        ~mqtt_publish() override= default;

        [[nodiscard]] std::size_t get_payload_length() const override {
            return this->payload_length;
        }
        void parse(const std::string & payload) override ;

        void accept(mqtt_visitor & v) override ;
        [[nodiscard]] const std::string & get_topic()const{
            return this->topic;
        }
        [[nodiscard]] const std::string & get_message()const{
            return this->message;
        }
        [[nodiscard]] const std::string & get_message_id()const{
            return this->message_id;
        }
        [[nodiscard]] constexpr pmq::u_int16 get_message_id_as_int()const{
            return this->message_id_as_int;
        }
        [[nodiscard]] constexpr pmq::u_int16 get_qos()const{
            return qos;
        }
        pmq::mqtt_publish create(std::shared_ptr<pmq::socket> & socket)const{
            mqtt_publish publish_msg(socket,payload_length,header);
            publish_msg.message = message;
            publish_msg.topic = topic;
            return publish_msg;
        }
        void send(std::shared_ptr<pmq::socket> & socket)const;

        [[nodiscard]] const std::string &get_client_id() const;

        void set_client_id(const std::string &clientId);
        [[nodiscard]] bool is_retained()const{
            return this->retain;
        }
    private:
        std::string client_id;

        std::string topic;
        std::string message;
        std::string message_id;
        pmq::u_int16 message_id_as_int;
    private:
        std::size_t payload_length;
        pmq::u_int8 header;
        bool dup;
        pmq::u_int16 qos;
        bool retain;
    };
}


#endif //PMQ_MQTT_PUBLISH_HPP
