//
// Created by pmqtt on 2019-06-29.
//
#include <algorithm>
#include <header/in_memory_storage.hpp>
#include <header/string.hpp>
#include <lib/message.hpp>
#include <random>
namespace {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1000);
}



void pmq::in_memory_storage::add_user(const std::string &name, const std::string &pwd) {
    std::unique_lock<std::mutex> guard(mutex);
    user_password_map[name] = pwd;
}

void pmq::in_memory_storage::add_subscriber(const std::string &client_id, std::string &topic) {

}

void pmq::in_memory_storage::remove_subcriber(const std::string &client_id, std::string &topic) {

}

bool pmq::in_memory_storage::check_user_password(const std::string &name, const std::string &pwd) {
    std::unique_lock<std::mutex> guard(mutex);
    return  user_password_map[name] == pwd;
}

bool pmq::in_memory_storage::exist_user(const std::string &name) {
    std::unique_lock<std::mutex> guard(mutex);
    return user_password_map.count(name) > 0;
}

void pmq::in_memory_storage::add_client(const std::string & client_id) {

}

void pmq::in_memory_storage::add_client_subscription(const std::string & clientId,
                             const std::string & topic,
                             pmq::subscriber & sub){

}


void pmq::in_memory_storage::add_will_message(const std::string & client_id,const pmq::message & message){

}


pmq::message pmq::in_memory_storage::get_will_message(const std::string & client_id) {
    std::unique_lock<std::mutex> guard(mutex);
    if(this->will_messages.count(client_id) > 0){
        return this->will_messages[client_id];
    }
    return pmq::message(" "," ",QOS_0);
}

void pmq::in_memory_storage::save_qos_two_message_id(const pmq::u_int16 &id, std::shared_ptr<pmq::mqtt_publish> &msg) {
    std::unique_lock<std::mutex> guard(mutex);
    this->message_storage[id] = msg;
}

std::shared_ptr<pmq::mqtt_publish> pmq::in_memory_storage::restore_qos_two_publish_msg(const pmq::u_int16 &id) {
    std::unique_lock<std::mutex> guard(mutex);
    if(this->message_storage.count(id) > 0){
        auto result =  this->message_storage[id];
        this->message_storage.erase(id);
        return result;
    }
    throw std::runtime_error("message id doesn't exists");
}

void pmq::in_memory_storage::save_qos_two_message_id(const std::string &id, const std::string &client_id) {
    std::unique_lock<std::mutex> guard(mutex);
    message_ids[client_id] = id;
}

std::string pmq::in_memory_storage::restore_qos_two_publish_msg(const std::string &client_id) {
    std::unique_lock<std::mutex> guard(mutex);
    if(this->message_ids.count(client_id) > 0){
        auto result =  this->message_ids[client_id];
        this->message_ids.erase(client_id);
        return result;
    }
    throw std::runtime_error("message id doesn't exists");
}

void pmq::in_memory_storage::add_client(std::shared_ptr<pmq::mqtt_connect> &client_connection) {
    std::unique_lock<std::mutex> guard(mutex);
    if(client_connection){
        std::string client_id = client_connection->get_client_id();
        if(client_connection->is_will_flag()){
            if(will_messages.count(client_id) < 1){
                pmq::QOS qos = pmq::create_qos_from_int(client_connection->get_will_qos());
                will_messages[client_id] = pmq::message(client_connection->get_will_topic(),
                        client_connection->get_will_payload(),qos);
            }else{

            }
        }
        if(client_connections.count(client_id) < 1) {
            client_connections[client_id] = client_connection;
        }
    }

}

void pmq::in_memory_storage::add_subscriber(const std::string &topic, const std::shared_ptr<pmq::subscriber> &subscriber) {
    std::unique_lock<std::mutex> guard(mutex);
    std::vector<std::string> topics = pmq::detail::split_topic(topic);
    if(topics.size() > 2){
        if(topics[0] == "$share"){
            std::string group = topics[1];
            std::vector<std::string> sub_topic;
            std::string shared_topic;
            for(std::size_t i = 2; i < topics.size();++i){
                shared_topic += topics[i]+"/";
            }
            std::cout<<"insert:" <<group <<" ... "<<shared_topic<<std::endl;
            this->shared_subscripted_clients[group].insert_subscriber(subscriber,shared_topic);
            return;
        }
    }

    this->subscripted_clients.insert_subscriber(subscriber,topic);
}

std::vector<std::shared_ptr<pmq::subscriber>> pmq::in_memory_storage::get_subscriber(const std::string &topic) {
    std::unique_lock<std::mutex> guard(mutex);
    std::vector<std::shared_ptr<pmq::subscriber>> vec = this->subscripted_clients.get_subscriber(topic);
    for(auto x : this->shared_subscripted_clients){
        auto tmp = x.second.get_subscriber(topic);
        if(!tmp.empty()) {
            int pos = static_cast<int>(dist(rng) % tmp.size());
            if (pos < tmp.size()) {
                vec.push_back(tmp[pos]);
            }
        }
    }
    return vec;
}

void pmq::in_memory_storage::add_retained_message(const std::shared_ptr<pmq::message> &msg) {
    std::unique_lock<std::mutex> guard(mutex);
    auto pred = [&](const std::shared_ptr<pmq::message> & item)->bool{
        return item->get_topic() == msg->get_topic();
    };

    auto it = std::find_if(this->retained_messages.begin(),this->retained_messages.end(),pred);
    if(it != this->retained_messages.end()) {
        this->retained_messages.erase(it);
    }
    this->retained_messages.emplace_back(msg);

}

void pmq::in_memory_storage::remove_client(const std::string & client_id){
    std::unique_lock<std::mutex> guard(mutex);
    if(client_connections.count(client_id) < 1) {
        client_connections.erase(client_id);
    }
}

void pmq::in_memory_storage::insert_configuration_for_subscribers(const pmq::config_module & config){
    cfg = config;
}


