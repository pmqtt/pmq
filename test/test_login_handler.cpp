//
// Created by pmqtt on 2019-07-18.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_login_handler

#include <boost/test/unit_test.hpp>

#include "header/exception/bad_connection_exception.hpp"
#include "../header/login_handler.hpp"
#include "../lib/mqtt_connect.hpp"
#include "../lib/socket.hpp"

class fake_storage : public pmq::storage{
public:
    std::string fake_name;
    std::string fake_password;
    fake_storage() = default;
    void add_user(const std::string &name, const std::string &pwd) override {

    }

    void add_subscriber(const std::string &client_id, std::string &topic) override {

    }

    void remove_subcriber(const std::string &client_id, std::string &topic) override {

    }

    bool check_user_password(const std::string &name, const std::string &pwd) override {
        return pwd == fake_password;
    }

    bool exist_user(const std::string &name) override {
        return name == fake_name;
    }
    void add_client(const std::string &client_id) override {

    }
    void add_client_subscription(const std::string &clientId, const std::string &topic, pmq::subscriber &sub) override {

    }
    void add_will_message(const std::string &client_id, const pmq::message &message) override {

    }
    pmq::message get_will_message(const std::string &client_id) override {
        return pmq::message();
    }
    void add_client(std::shared_ptr<pmq::mqtt_connect> &client_connection) override {

    }
    void save_qos_two_message_id(const pmq::u_int16 &id, std::shared_ptr<pmq::mqtt_publish> &msg) override {

    }
    std::shared_ptr<pmq::mqtt_publish> restore_qos_two_publish_msg(const pmq::u_int16 &id) override {
        return std::shared_ptr<pmq::mqtt_publish>();
    }
    void save_qos_two_message_id(const std::string &id, const std::string &client_id) override {

    }
    std::string restore_qos_two_publish_msg(const std::string &client_id) override {
        return std::string();
    }
    void add_subscriber(const std::string &topic, const std::shared_ptr<pmq::subscriber> &subscriber) override {

    }
    std::vector<std::shared_ptr<pmq::subscriber>> get_subscriber(const std::string &topic) override {
        return std::vector<std::shared_ptr<pmq::subscriber>>();
    }
    std::map<std::string, pmq::message> get_all_will_messages() const override {
        return std::map<std::string, pmq::message>();
    }

    void add_retained_message(const std::shared_ptr<pmq::message> &msg) override {

    }
    std::vector<std::shared_ptr<pmq::message>> get_retained_messages()const override {
        return  std::vector<std::shared_ptr<pmq::message>>();
    }
    void remove_client(const std::string & client_id) override {}
    void insert_configuration_for_subscribers(const pmq::config_module & config) override {}
    const pmq::config_module & get_configuration_for_subscribers()const override {}

};

pmq::mqtt_connect * create_fake_mqtt_connect(){
    pmq::mqtt_connect * connect = new pmq::mqtt_connect();
    connect->set_user_name_flag();
    connect->set_user_name("pmqtt");
    connect->set_password("1234");
    return connect;
}

BOOST_AUTO_TEST_CASE( TEST_LOGIN_HANDLER )
{
    std::shared_ptr<fake_storage> fake(new fake_storage);
    fake->fake_name = "pmqtt";
    fake->fake_password = "1234";
    pmq::mqtt_connect * connect = create_fake_mqtt_connect();
    pmq::login_handler handler;
    try {
        handler.handle(fake, connect);
        BOOST_CHECK(true);
    }catch(...){
        BOOST_CHECK(false);
    }
    delete connect;
}

BOOST_AUTO_TEST_CASE( TEST_FAILED_LOGIN_NO_USER_HANDLER )
{
    std::shared_ptr<fake_storage> fake(new fake_storage);
    fake->fake_name = "test";
    fake->fake_password = "1234";
    pmq::mqtt_connect * connect = create_fake_mqtt_connect();

    pmq::login_handler handler;
    try {
        handler.handle(fake, connect);
        BOOST_CHECK(false);
    }catch(pmq::exception::bad_connection_exception e){
        BOOST_CHECK(true);
    }
    delete connect;
}

BOOST_AUTO_TEST_CASE( TEST_FAILED_LOGIN_WRONG_PASSWORD_HANDLER )
{
    std::shared_ptr<fake_storage> fake(new fake_storage);
    fake->fake_name = "pmqtt";
    fake->fake_password = "12345";
    pmq::mqtt_connect * connect = create_fake_mqtt_connect();

    pmq::login_handler handler;
    try {
        handler.handle(fake, connect);
        BOOST_CHECK(false);
    }catch(pmq::exception::bad_connection_exception e){
        BOOST_CHECK(true);
    }
    delete connect;
}

BOOST_AUTO_TEST_CASE( TEST_FAILED_LOGIN_NO_USER_FLAG_HANDLER )
{
    std::shared_ptr<fake_storage> fake(new fake_storage);
    fake->fake_name = "pmqtt";
    fake->fake_password = "12345";
    pmq::mqtt_connect connect;
    pmq::login_handler handler;
    try {
        handler.handle(fake, &connect);
        BOOST_CHECK(false);
    }catch(pmq::exception::bad_connection_exception e){
        BOOST_CHECK(true);
    }
}

