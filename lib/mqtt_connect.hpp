//
// Created by PMQTT on 2019-03-30.
//

#ifndef PMQ_MQTT_CONNECT_HPP
#define PMQ_MQTT_CONNECT_HPP

namespace pmq {
    class mqtt_package;
    class mqtt_api;

    class mqtt_connect : public mqtt_package{
    public:
        mqtt_connect(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length);
        virtual ~mqtt_connect(){}

        std::size_t get_payload_length() const override {
            return this->payload_length;
        }
        void parse(const std::string & payload) override ;

        const std::string & get_client_id()const{
            return this->client_id;
        }

        void accept(mqtt_visitor & v) override ;
    private:
        std::size_t payload_length;

        pmq::u_int8 msb;
        pmq::u_int8 lsb;
        unsigned int version;
        unsigned int keep_alive;
        bool user_name_flag;
        bool password_flag;
        bool will_retain;
        std::size_t will_qos;
        bool will_flag;
        bool clean_start;
        bool reserved;
        std::string client_id;
        std::string will_topic;
        std::string will_payload;
        std::string user_name;
        std::string password;
        std::shared_ptr<pmq::mqtt_api> api;
    };

}


#endif //PMQ_MQTT_CONNECT_HPP
