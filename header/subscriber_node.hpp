//
// Created by pmqtt on 2019-07-22.
//

#ifndef PMQ_SUBSCRIBER_NODE_HPP
#define PMQ_SUBSCRIBER_NODE_HPP
#include <map>
#include <string>
#include <lib/socket.hpp>
#include <lib/subscriber.hpp>
#include <vector>


namespace pmq::detail{


    typedef std::pair<std::shared_ptr<pmq::subscriber>,bool> subscriber_item;

    class subscriber_node{
    public:
        subscriber_node(std::string sub_topic);
        ~subscriber_node();

        void add_subscriber(const std::shared_ptr<pmq::subscriber> & sub,bool is_wildcard);
        void remove_subsriber(const std::shared_ptr<pmq::subscriber> & sub);
        std::vector<std::shared_ptr<pmq::subscriber>> get_all_wildcard_subscriber()const;
        std::vector<std::shared_ptr<pmq::subscriber>> get_subscribers()const;
        void add_child(const std::string & topic,const std::shared_ptr<subscriber_node> & node);


        std::string get_sub_topic()const{
            return sub_topic;
        }
        std::shared_ptr<subscriber_node> get_child(const std::string & topic);
        bool exist_child(const std::string & topic);


    private:
        std::string sub_topic;
        std::vector<subscriber_item> subscriber_list;
        std::map<std::string,std::shared_ptr<subscriber_node>> childs;

    };
}

#endif //PMQ_SUBSCRIBER_NODE_HPP
