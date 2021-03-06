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
        mqtt_connect() = default;
        mqtt_connect(std::shared_ptr<pmq::socket> & client_socket, std::size_t payload_length);
        ~mqtt_connect() override = default;

        [[nodiscard]] std::size_t get_payload_length() const override {
            return this->payload_length;
        }
        void parse(const std::string & payload) override ;

        [[nodiscard]] const std::string & get_client_id()const{
            return this->client_id;
        }

        void accept(mqtt_visitor & v) override ;

        [[nodiscard]] unsigned int get_version() const {
            return version;
        }

        [[nodiscard]] unsigned int get_keep_alive() const {
            return keep_alive;
        }
        void set_user_name_flag(){
            user_name_flag = true;
        }

        [[nodiscard]] bool is_user_name_flag() const {
            return user_name_flag;
        }

        [[nodiscard]] bool is_password_flag() const {
            return password_flag;
        }

        [[nodiscard]] bool is_will_retain() const {
            return will_retain;
        }

        [[nodiscard]] size_t get_will_qos() const {
            return will_qos;
        }

        [[nodiscard]] bool is_will_flag() const {
            return will_flag;
        }

        [[nodiscard]] bool is_clean_start() const {
            return clean_start;
        }

        [[nodiscard]] bool is_reserved() const {
            return reserved;
        }

        [[nodiscard]] const std::string &get_will_topic() const {
            return will_topic;
        }

        [[nodiscard]] const std::string &get_will_payload() const {
            return will_payload;
        }

        [[nodiscard]] const std::string &get_user_name() const {
            return user_name;
        }

        [[nodiscard]] const std::string &get_password() const {
            return password;
        }

        [[nodiscard]]const std::shared_ptr<mqtt_api> &get_api() const {
            return api;
        }

    private:
        std::size_t payload_length;

        pmq::u_int8 msb;
        pmq::u_int8 lsb;
        unsigned int version;
        unsigned int keep_alive;
        bool user_name_flag = false;
        bool password_flag = false;
        bool will_retain;
        std::size_t will_qos;

    private:
        bool will_flag;
        bool clean_start;
        bool reserved;
        std::string client_id;

    private:
        std::string will_topic;
    public:
        void set_will_topic(const std::string &willTopic) {
            will_topic = willTopic;
        }

        void set_will_payload(const std::string &willPayload) {
            will_payload = willPayload;
        }

        void set_user_name(const std::string &userName) {
            user_name = userName;
        }

        void set_password(const std::string &pwd) {
            this->password = pwd;
        }

    private:
        std::string will_payload;
        std::string user_name;
        std::string password;
        std::shared_ptr<pmq::mqtt_api> api;
    };

}


#endif //PMQ_MQTT_CONNECT_HPP
