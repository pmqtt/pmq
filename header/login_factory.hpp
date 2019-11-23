//
// Created by pmqtt on 2019-07-07.
//

#ifndef PMQ_LOGIN_FACTORY_HPP
#define PMQ_LOGIN_FACTORY_HPP
#include "login_handler.hpp"
namespace pmq{
    class login_factory{
    public:
        [[nodiscard]] virtual std::shared_ptr<pmq::login_handler> create(bool anonymous)const;
    };
}

#endif //PMQ_LOGIN_FACTORY_HPP
