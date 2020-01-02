//
// Created by pmqtt on 2019-07-07.
//
#include <lib/exception/login_exception.hpp>
#include <lib/server/login/login_handler.hpp>
#include <lib/exception/bad_connection_exception.hpp>

namespace pmq{
    void login_handler::handle(const pmq::config & cfg,const std::shared_ptr<pmq::storage> & storage_service, pmq::mqtt_connect * msg){
        const std::string exception_text("User name or password are wrong");
        bool hasEntrance = true;
        bool use_client_certificate_as_username = cfg.is_client_certificate_username();
        if(use_client_certificate_as_username){
            auto subject = msg->get_socket()->get_normalized_subject_name();
            BOOST_LOG_TRIVIAL(debug)<<"Use client certificate as username: "<<subject;
            if(!subject.empty()) {
                msg->set_user_name_flag();
                msg->set_user_name(subject);
            }else{
                use_client_certificate_as_username = false;
            }
        }


        if(msg->is_user_name_flag()) {
            BOOST_LOG_TRIVIAL(debug)<<"user flag was set";
            if (storage_service->exist_user(msg->get_user_name())) {
                if(use_client_certificate_as_username){
                    BOOST_LOG_TRIVIAL(debug)<<"Access allowes because client certificate is valid!";
                    return;
                }
                if (!storage_service->check_user_password(msg->get_user_name(), msg->get_password())) {
                    throw pmq::exception::login_exception(exception_text.c_str());
                }
            } else {
                throw pmq::exception::login_exception(exception_text.c_str());
            }
        }
        else{
            throw pmq::exception::bad_connection_exception(exception_text.c_str());
        }
    }
}