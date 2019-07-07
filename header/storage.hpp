//
// Created by pmqtt on 2019-06-23.
//

#ifndef PMQ_STORAGE_HPP
#define PMQ_STORAGE_HPP
#include <string>
#include <lib/mqtt_package.hpp>
#include <lib/mqtt_publish.hpp>
#include <lib/socket.hpp>
#include <lib/subscriber.hpp>
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

        virtual void add_client(const std::string & client_id) = 0;
        virtual void add_client_subscription(const std::string & clientId,
                                                const std::string & topic,
                                                pmq::subscriber & sub) = 0;

        virtual void save_qos_two_message_id(const pmq::u_int16  & id , std::shared_ptr<pmq::mqtt_publish> & msg ) = 0;
        virtual std::shared_ptr<pmq::mqtt_publish> restore_qos_two_publish_msg(const pmq::u_int16 & id) = 0;
    };

}

#endif //PMQ_STORAGE_HPP
