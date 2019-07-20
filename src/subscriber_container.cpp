//
// Created by pmqtt on 2019-07-19.
//
#include<algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <header/subscriber_container.hpp>

#include <stack>

namespace pmq::string{
    std::vector <std::string> split(const std::string &str, const char *delim) {
        std::vector<std::string> splitted;
        boost::split(splitted, str, boost::is_any_of(delim));
        return splitted;
    }
}

std::vector<std::string> create_sub_topic_vec(const std::vector<std::string> & vec,std::size_t pos){
    std::vector<std::string> result;
    //a/k/t
    if(vec.size() < pos +2){
        for(std::size_t i = pos+2; i< vec.size();++i ){
            result.push_back(vec[i]);
        }
    }
    return result;
}

pmq::detail::subscriber_container::subscriber_container() {
    root = std::make_shared<subscriber_node>("#");
}

pmq::detail::subscriber_container::~subscriber_container() {

}

std::size_t pmq::detail::subscriber_container::get_size() const {
    return 0;
}

void pmq::detail::subscriber_container::insert_subscriber(const std::shared_ptr<pmq::subscriber> & sub,const std::string & topic) {
    if(topic =="#"){
        root->add_subscriber(sub,true);
        return;
    }
    node_ptr iter = root;
    std::vector<std::string> sub_topics = detail::split_topic(topic);


    while(sub_topics.size() > 0) {
        if (iter->exist_child(sub_topics[0])) {
            if (sub_topics.size() > 0) {
                if (sub_topics[1] == "#") {
                    iter = iter->get_child(sub_topics[0]);
                    iter->add_subscriber(sub, true);
                    break;
                } else {
                    iter = iter->get_child(sub_topics[0]);
                    sub_topics.erase(sub_topics.begin());
                }
            } else {
                iter->add_subscriber(sub, true);
                break;
            }
        }else{
            bool is_last_sub_topic_wild_card = false;
            for(const std::string sub_topic : sub_topics){
                if(sub_topic != "#") {
                    node_ptr child = std::make_shared<subscriber_node>(sub_topic);
                    iter->add_child(sub_topic, child);
                    iter = child;
                }else{
                    is_last_sub_topic_wild_card = true;
                    break;
                }

            }

            iter->add_subscriber(sub,is_last_sub_topic_wild_card);
            break;
        }
    }


}

std::vector<std::shared_ptr<pmq::subscriber>> pmq::detail::subscriber_container::get_subscriber(const std::string &topic) {

    if(!root){
        return std::vector<std::shared_ptr<pmq::subscriber>>();
    }

    if(topic == "#"){
        return root->get_subscribers();
    }
    if(topic.length() == 0){
        return std::vector<std::shared_ptr<pmq::subscriber>>();
    }

    std::stack<std::pair<node_ptr,std::vector<std::string>>> iter_stack;
    std::vector<std::shared_ptr<pmq::subscriber>> result;
    node_ptr iter = root;

    std::vector<std::string> sub_topics = detail::split_topic(topic);

    if(sub_topics.size() == 1){
        if(sub_topics[0] == " "){
            return std::vector<std::shared_ptr<pmq::subscriber>>();

        }
        iter = iter->get_child(sub_topics[0]);
        if(iter) {
            return iter->get_subscribers();
        }else{
            return root->get_subscribers();
        }
    }
    for(std::size_t i =0; i< sub_topics.size()-1;++i){
        auto vec = iter->get_all_wildcard_subscriber();
        std::copy(vec.begin(),vec.end(),std::back_inserter(result));
        if(iter->exist_child(sub_topics[i])) {
            iter_stack.push(std::pair(iter->get_child(sub_topics[i]),create_sub_topic_vec(sub_topics,i)));
            iter = iter->get_child(sub_topics[i]);
            if(i+1 >= sub_topics.size()-1){
                auto vec = iter->get_all_wildcard_subscriber();
                std::copy(vec.begin(),vec.end(),std::back_inserter(result));
            }
        } else{
            break;
        }
    }
    if(iter->exist_child(sub_topics[sub_topics.size()-1])) {
        iter = iter->get_child(sub_topics[sub_topics.size()-1]);
        auto vec = iter->get_subscribers();
        std::copy(vec.begin(), vec.end(), std::back_inserter(result));
    }


    return result;

}





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


std::vector<std::string> pmq::detail::split_topic(const std::string &topic) {
    if(topic.length() == 0){ return std::vector<std::string>(); }
    bool is_first_sign_a_slash = false;
    if(topic[0] == '/'){
        is_first_sign_a_slash = true;
    }
    std::vector<std::string> splited = pmq::string::split(topic,"/");
    if( is_first_sign_a_slash ){
        splited.erase(splited.begin());
        splited[0] = "/"+splited[0];
    }
    if(splited[splited.size()-1].length() == 0){
        splited.pop_back();
    }
    return splited;
}
