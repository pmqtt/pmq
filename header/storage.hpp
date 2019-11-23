//
// Created by pmqtt on 2019-06-23.
//

#ifndef PMQ_STORAGE_HPP
#define PMQ_STORAGE_HPP
#include <string>
#include <lib/mqtt_package.hpp>
#include <lib/mqtt_connect.hpp>
#include <lib/message.hpp>
#include <lib/mqtt_publish.hpp>
#include <lib/socket.hpp>
#include <lib/subscriber.hpp>
#include <header/module/config_module.hpp>

namespace pmq{

    class storage{
    public:
        storage()= default;
        virtual ~storage()= default;

        virtual void add_user(const std::string & name,const std::string & pwd) = 0;
        virtual void add_subscriber(const std::string & client_id, std::string & topic) = 0;
        virtual void remove_subcriber(const std::string &client_id, std::string & topic) = 0;
        virtual bool check_user_password(const std::string & name,const std::string & pwd) = 0;
        virtual bool exist_user(const std::string & name) = 0;

        virtual void add_retained_message(const std::shared_ptr<pmq::message> & msg) = 0;
        virtual std::vector<std::shared_ptr<pmq::message>> get_retained_messages()const = 0;
        virtual void add_client(const std::string & client_id) = 0;
        virtual void add_client_subscription(const std::string & clientId,
                                                const std::string & topic,
                                                pmq::subscriber & sub) = 0;

        virtual void add_will_message(const std::string & client_id,const pmq::message & message) = 0;
        virtual pmq::message get_will_message(const std::string & client_id) =0 ;

        virtual void add_client(std::shared_ptr<pmq::mqtt_connect> & client_connection) = 0;
        virtual void remove_client(const std::string & client_id) = 0;

        virtual void save_qos_two_message_id(const pmq::u_int16  & id , std::shared_ptr<pmq::mqtt_publish> & msg ) = 0;
        virtual std::shared_ptr<pmq::mqtt_publish> restore_qos_two_publish_msg(const pmq::u_int16 & id) = 0;
        virtual void save_qos_two_message_id(const std::string & id , const std::string &client_id ) = 0;
        virtual std::string  restore_qos_two_publish_msg(const std::string & client_id ) = 0;

        virtual void add_subscriber(const std::string &topic, const std::shared_ptr<pmq::subscriber> & subscriber) = 0;
        virtual std::vector<std::shared_ptr<pmq::subscriber>> get_subscriber(const std::string & topic) = 0;
        virtual std::map<std::string,pmq::message> get_all_will_messages()const = 0;

        virtual void insert_configuration_for_subscribers(const pmq::config_module & config)=0;
        virtual const pmq::config_module & get_configuration_for_subscribers()const =0;


    };

}

#endif //PMQ_STORAGE_HPP
