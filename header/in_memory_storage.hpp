//
// Created by pmqtt on 2019-06-29.
//

#ifndef PMQ_IN_MEMORY_STORAGE_HPP
#define PMQ_IN_MEMORY_STORAGE_HPP
#include <boost/thread.hpp>
#include<map>

#include "subscriber_container.hpp"
#include "storage.hpp"

namespace pmq{


    class in_memory_storage : public pmq::storage{
    public:
        in_memory_storage();

        virtual ~in_memory_storage();

        void add_user(const std::string &name, const std::string &pwd) override;

        void add_subscriber(const std::string &client_id, std::string &topic) override;

        void remove_subcriber(const std::string &client_id, std::string &topic) override;

        void add_will_message(const std::string & client_id,const pmq::message & message) override ;


        pmq::message get_will_message(const std::string & client_id) override ;

        bool check_user_password(const std::string &name, const std::string &pwd) override;


        bool exist_user(const std::string &name) override;

        void add_client(const std::string & client_id) override;

        void add_client_subscription(const std::string & clientId,
                                             const std::string & topic,
                                             pmq::subscriber & sub) override ;

        void save_qos_two_message_id(const pmq::u_int16  & id , std::shared_ptr<pmq::mqtt_publish> & msg ) override;
        std::shared_ptr<pmq::mqtt_publish> restore_qos_two_publish_msg(const pmq::u_int16 & id) override;

        void save_qos_two_message_id(const std::string  & id , const std::string &client_id ) override;
        std::string restore_qos_two_publish_msg(const std::string & client_id ) override ;
        void add_client(std::shared_ptr<pmq::mqtt_connect> & client_connection) override ;

        void add_subscriber(const std::string topic,const std::shared_ptr<pmq::subscriber> & subscriber) override ;

        void add_retained_message(const std::shared_ptr<pmq::message> & msg) override;
        std::vector<std::shared_ptr<pmq::message>> get_retained_messages()const override{
            return this->retained_messages;
        }


        std::vector<std::shared_ptr<pmq::subscriber>> get_subscriber(const std::string & topic) override;
        std::map<std::string,pmq::message> get_all_will_messages()const override {
            return this->will_messages;
        }


    private:
        std::map<std::string,std::string> user_password_map;
        std::map<pmq::u_int16 , std::shared_ptr<pmq::mqtt_publish> > message_storage;
        std::map<std::string, std::string > message_ids;
        std::map<std::string,pmq::message> will_messages;
        std::map<std::string,std::shared_ptr<pmq::mqtt_connect>> client_connections;
        pmq::detail::subscriber_container subscripted_clients;
        std::map<std::string,pmq::detail::subscriber_container> shared_subscripted_clients;
        std::vector<std::shared_ptr<pmq::message>> retained_messages;
        boost::mutex mutex;
    };
}

#endif //PMQ_IN_MEMORY_STORAGE_HPP
