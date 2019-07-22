//
// Created by pmqtt on 2019-07-19.
//

#ifndef PMQ_SUBSCRIBER_CONTAINER_HPP
#define PMQ_SUBSCRIBER_CONTAINER_HPP
#include "subscriber_node.hpp"
namespace pmq::detail{


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
