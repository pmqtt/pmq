//
// Created by pmqtt on 2019-06-29.
//

#ifndef PMQ_IN_MEMORY_STORAGE_HPP
#define PMQ_IN_MEMORY_STORAGE_HPP
#include <boost/thread.hpp>
#include<map>

#include "storage.hpp"

namespace pmq{


    class in_memory_storage : public pmq::storage{
    public:
        in_memory_storage();

        virtual ~in_memory_storage();

        void add_user(const std::string &name, const std::string &pwd) override;

        void add_subscriber(const std::string &client_id, std::string &topic) override;

        void remove_subcriber(const std::string &client_id, std::string &topic) override;

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



    private:
        std::map<std::string,std::string> user_password_map;
        std::map<pmq::u_int16 , std::shared_ptr<pmq::mqtt_publish> > message_storage;
        std::map<std::string, std::string > message_ids;

        boost::mutex mutex;
    };
}

#endif //PMQ_IN_MEMORY_STORAGE_HPP
