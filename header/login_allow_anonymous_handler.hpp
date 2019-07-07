//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_LOGIN_ALLOW_ANONYMOUS_HANDLER_HPP
#define PMQ_LOGIN_ALLOW_ANONYMOUS_HANDLER_HPP

#include "login_handler.hpp"
namespace pmq{
    class login_allow_anonymous_handler : public login_handler{
    public:
        login_allow_anonymous_handler() = default;
        virtual ~login_allow_anonymous_handler() = default;

        void handle(const std::shared_ptr<pmq::storage> &storage,const pmq::mqtt_connect * msg) override ;
    };
}

#endif //PMQ_LOGIN_ALLOW_ANONYMOUS_HANDLER_HPP
