//
// Created by pmqtt on 2019-07-07.
//
#include <header/exception/login_exception.hpp>
#include "header/login_handler.hpp"
#include "header/exception/bad_connection_exception.hpp"
#include "header/exception/login_exception.hpp"
namespace pmq{
    void login_handler::handle(const std::shared_ptr<pmq::storage> & storage_service,const pmq::mqtt_connect * msg){
        bool hasEntrance = true;
        if(msg->is_user_name_flag()){
            if(storage_service->exist_user(msg->get_user_name())){
                if(!storage_service->check_user_password(msg->get_user_name(),msg->get_password())){
                    throw pmq::exception::login_exception("User name or password are wrong");
                }
            }else{
                throw pmq::exception::login_exception("User name or password are wrong");
            }
        }else{
            throw pmq::exception::bad_connection_exception("User name or password are wrong");
        }
    }
}