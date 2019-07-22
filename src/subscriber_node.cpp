//
// Created by pmqtt on 2019-07-22.
//
#include "header/subscriber_node.hpp"
pmq::detail::subscriber_node::subscriber_node(std::string sub_topic)
        :sub_topic(sub_topic){

}

pmq::detail::subscriber_node::~subscriber_node() {}

void pmq::detail::subscriber_node::add_subscriber(const std::shared_ptr<pmq::subscriber> &sub, bool is_wildcard) {
    subscriber_item item(sub,is_wildcard);
    subscriber_list.emplace_back(item);
}

std::vector<std::shared_ptr<pmq::subscriber>> pmq::detail::subscriber_node::get_all_wildcard_subscriber() const {
    std::vector<std::shared_ptr<pmq::subscriber>> result;
    for( auto & x : subscriber_list){
        if(x.second){
            result.emplace_back(x.first);
        }
    }
    return result;
}

std::vector<std::shared_ptr<pmq::subscriber>> pmq::detail::subscriber_node::get_subscribers() const {
    std::vector<std::shared_ptr<pmq::subscriber>> result;
    for( auto & x : subscriber_list){
        result.emplace_back(x.first);
    }
    return result;
}

void pmq::detail::subscriber_node::add_child(const std::string &topic,
                                             const std::shared_ptr<pmq::detail::subscriber_node> &node) {
    childs[topic] = node;
}

bool pmq::detail::subscriber_node::exist_child(const std::string &topic) {
    return childs.count(topic)> 0;
}

void pmq::detail::subscriber_node::remove_subsriber(const std::shared_ptr<pmq::subscriber> &sub) {

    for(auto iter = subscriber_list.begin(); iter != subscriber_list.end(); iter++){
        if(iter->first.get() == sub.get()){
            subscriber_list.erase(iter);
            return;
        }
    }
}

std::shared_ptr<pmq::detail::subscriber_node> pmq::detail::subscriber_node::get_child(const std::string &topic) {
    if(childs.count(topic)> 0){
        return childs[topic];
    }
    return nullptr;
}
