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


