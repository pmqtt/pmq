//
// Created by pmqtt on 2019-06-23.
//

#ifndef PMQ_STORAGE_HPP
#define PMQ_STORAGE_HPP
#include <string>
namespace pmq{

    class storage{
    public:
        storage(){}
        virtual ~storage(){}

        virtual void add_user(const std::string & name,const std::string & pwd) = 0;
        virtual void add_subscriber(const std::string & client_id, std::string & topic) = 0;
        virtual void remove_subcriber(const std::string &client_id, std::string & topic) = 0;
        virtual bool check_user_password(const std::string & name,const std::string & pwd) = 0;
        virtual bool exist_user(const std::string & name) = 0;

    };

}

#endif //PMQ_STORAGE_HPP
