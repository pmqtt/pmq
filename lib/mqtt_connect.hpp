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
        virtual ~mqtt_connect() = default;

        std::size_t get_payload_length() const override {
            return this->payload_length;
        }
        void parse(const std::string & payload) override ;

        const std::string & get_client_id()const{
            return this->client_id;
        }

        void accept(mqtt_visitor & v) override ;

        unsigned int get_version() const {
            return version;
        }

        unsigned int get_keep_alive() const {
            return keep_alive;
        }

        bool is_user_name_flag() const {
            return user_name_flag;
        }

        bool is_password_flag() const {
            return password_flag;
        }

        bool is_will_retain() const {
            return will_retain;
        }

        size_t get_will_qos() const {
            return will_qos;
        }

        bool is_will_flag() const {
            return will_flag;
        }

        bool is_clean_start() const {
            return clean_start;
        }

        bool is_reserved() const {
            return reserved;
        }

        const std::string &get_will_topic() const {
            return will_topic;
        }

        const std::string &get_will_payload() const {
            return will_payload;
        }

        const std::string &get_user_name() const {
            return user_name;
        }

        const std::string &get_password() const {
            return password;
        }

        const std::shared_ptr<mqtt_api> &get_api() const {
            return api;
        }

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

    private:
        bool will_flag;
        bool clean_start;
        bool reserved;
        std::string client_id;

    private:
        std::string will_topic;
        std::string will_payload;
        std::string user_name;
        std::string password;
        std::shared_ptr<pmq::mqtt_api> api;
    };

}


#endif //PMQ_MQTT_CONNECT_HPP
