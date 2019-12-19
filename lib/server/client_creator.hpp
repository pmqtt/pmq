//
// Created by pmqtt on 2019-07-04.
//

#ifndef PMQ_CLIENT_CREATOR_HPP
#define PMQ_CLIENT_CREATOR_HPP

#include <map>
#include "lib/network/client_factory.hpp"
#include "startup_configuration.hpp"

namespace pmq{
    typedef std::function<std::shared_ptr<pmq::client_factory>(const pmq::config &)> creator_func;

    struct client_creator{
        client_creator() = default;
        virtual ~client_creator() = default;
        void bind_creator(const std::string & id,const creator_func & func){
            creator_functions[id] = func;
        }
        creator_func get(const std::string & id)const{
            if(creator_functions.count(id) > 0){
                return creator_functions[id];
            }
            throw pmq::exception::config_exception(id + " doesn't configured for creator");
        }
    private:
        static std::map<std::string,creator_func> creator_functions;
    };

    std::map<std::string,creator_func> client_creator::creator_functions;

}

#endif //PMQ_CLIENT_CREATOR_HPP
