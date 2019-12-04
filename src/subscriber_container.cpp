//
// Created by pmqtt on 2019-07-19.
//

#include<algorithm>
#include "header/string.hpp"
#include "header/subscriber_container.hpp"



std::vector<std::string> create_sub_topic_vec(const std::vector<std::string> & vec,std::size_t pos){
    std::vector<std::string> result;
    for(std::size_t i = pos+1; i< vec.size();++i ){
        result.push_back(vec[i]);
    }

    return result;
}

pmq::detail::subscriber_container::subscriber_container() {
    root = std::make_shared<subscriber_node>("#");
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


    while(!sub_topics.empty()) {
        if (iter->exist_child(sub_topics[0])) {
            if (sub_topics.size() > 1) {
                if (sub_topics[1] == "#") {
                    iter = iter->get_child(sub_topics[0]);
                    iter->add_subscriber(sub, true);
                    break;
                } else {
                    iter = iter->get_child(sub_topics[0]);
                    sub_topics.erase(sub_topics.begin());
                }
            } else {
                iter = iter->get_child(sub_topics[0]);
                iter->add_subscriber(sub, true);
                break;
            }
        }else{
            bool is_last_sub_topic_wild_card = false;
            for(const std::string & sub_topic : sub_topics){
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

    return tree_down(this->root,pmq::detail::split_topic(topic));

}

std::vector<std::shared_ptr<pmq::subscriber>>
pmq::detail::subscriber_container::tree_down(const pmq::detail::node_ptr &root,
                                             const std::vector<std::string>& sub_topics) {


    std::vector<std::shared_ptr<pmq::subscriber>> result;
    node_ptr iter = root;


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
    node_ptr parent;
    for(std::size_t i =0; i< sub_topics.size()-1;++i){
        auto vec = iter->get_all_wildcard_subscriber();
        std::copy(vec.begin(),vec.end(),std::back_inserter(result));

        parent = iter;
        if(iter->exist_child(sub_topics[i])) {
            iter = iter->get_child(sub_topics[i]);
            if(i+1 >= sub_topics.size()-1){
                vec = iter->get_all_wildcard_subscriber();
                std::copy(vec.begin(),vec.end(),std::back_inserter(result));
            }
        }else if(parent->exist_child("+")){
            std::vector<std::shared_ptr<pmq::subscriber>> plus_subscribtors =  tree_down(parent->get_child("+"),create_sub_topic_vec(sub_topics,i));
            std::copy(plus_subscribtors.begin(),plus_subscribtors.end(),std::back_inserter(result));
        }
        else{
            break;
        }

    }

    if(iter->exist_child(sub_topics[sub_topics.size()-1])) {
        iter = iter->get_child(sub_topics[sub_topics.size()-1]);
        auto vec = iter->get_subscribers();
        std::copy(vec.begin(), vec.end(), std::back_inserter(result));
    }
    if(parent->exist_child("+")){
        auto vec = create_sub_topic_vec(sub_topics,sub_topics.size()-2);
        std::vector<std::shared_ptr<pmq::subscriber>> plus_subscribers =  tree_down(parent->get_child("+"),vec);
        std::copy(plus_subscribers.begin(),plus_subscribers.end(),std::back_inserter(result));
    }

    return result;
}





