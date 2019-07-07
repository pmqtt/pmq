//
// Created by pmqtt on 2019-07-07.
//
#include "header/login_factory.hpp"
#include "header/login_handler.hpp"
#include "header/login_allow_anonymous_handler.hpp"

namespace pmq{
    std::shared_ptr<pmq::login_handler> login_factory::create(bool anonymous)const{
        if(anonymous){
            return std::make_shared<pmq::login_allow_anonymous_handler>();
        }
        return std::make_shared<pmq::login_handler>();
    }
}
