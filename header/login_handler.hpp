//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_LOGIN_HANDLER_HPP
#define PMQ_LOGIN_HANDLER_HPP

#include "storage.hpp"
#include "lib/mqtt_connect.hpp"

namespace pmq{
    class login_handler{
    public:
        login_handler() = default;
        virtual ~login_handler() = default;

        virtual void handle(const std::shared_ptr<pmq::storage> & storage,const pmq::mqtt_connect * msg);
    };
}

#endif //PMQ_LOGIN_HANDLER_HPP
