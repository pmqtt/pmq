//
// Created by pmqtt on 2019-06-29.
//

#include <header/in_memory_storage.hpp>


pmq::in_memory_storage::in_memory_storage() {

}


pmq::in_memory_storage::~in_memory_storage() {

}

void pmq::in_memory_storage::add_user(const std::string &name, const std::string &pwd) {
    boost::unique_lock<boost::mutex> guard(mutex);
    user_password_map[name] = pwd;
}

void pmq::in_memory_storage::add_subscriber(const std::string &client_id, std::string &topic) {

}

void pmq::in_memory_storage::remove_subcriber(const std::string &client_id, std::string &topic) {

}

bool pmq::in_memory_storage::check_user_password(const std::string &name, const std::string &pwd) {
    boost::unique_lock<boost::mutex> guard(mutex);
    return  user_password_map[name] == pwd;
}

bool pmq::in_memory_storage::exist_user(const std::string &name) {
    boost::unique_lock<boost::mutex> guard(mutex);
    return user_password_map.count(name) > 0;
}

void pmq::in_memory_storage::add_client(const std::string & client_id) {

}

void pmq::in_memory_storage::add_client_subscription(const std::string & clientId,
                             const std::string & topic,
                             pmq::subscriber & sub){

}

void pmq::in_memory_storage::save_qos_two_message_id(const pmq::u_int16 &id, std::shared_ptr<pmq::mqtt_publish> &msg) {
    this->message_storage[id] = msg;
}

std::shared_ptr<pmq::mqtt_publish> pmq::in_memory_storage::restore_qos_two_publish_msg(const pmq::u_int16 &id) {
    if(this->message_storage.count(id) > 0){
        return this->message_storage[id];
    }
    throw std::runtime_error("message id doesn't exists");
}
