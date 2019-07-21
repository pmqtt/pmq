//
// Created by pmqtt on 2019-07-19.
//

#ifndef PMQ_SUBSCRIBER_CONTAINER_HPP
#define PMQ_SUBSCRIBER_CONTAINER_HPP
#include <map>
#include <string>
#include <lib/socket.hpp>
#include <lib/subscriber.hpp>
#include <vector>
namespace pmq::detail{

    std::vector<std::string> split_topic(const std::string & topic);

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

    typedef std::shared_ptr<subscriber_node> node_ptr;

    class subscriber_container{
    public:
        subscriber_container();
        ~subscriber_container();
        void insert_subscriber(const std::shared_ptr<pmq::subscriber> & sub,const std::string & topic);
        std::vector<std::shared_ptr<pmq::subscriber>> get_subscriber(const std::string & topic);
        std::size_t get_size()const;

    private:
       static std::vector<std::shared_ptr<pmq::subscriber>> tree_down(const node_ptr & root,const std::vector<std::string>& sub_topics);

    private:
        node_ptr root; // is always '#'

    };
}

#endif //PMQ_SUBSCRIBER_CONTAINER_HPP
