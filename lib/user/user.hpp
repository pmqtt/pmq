//
// Created by pmq on 02.01.20.
//

#ifndef PMQ_USER_HPP
#define PMQ_USER_HPP
#include <string>
namespace pmq{

    struct rule{
        enum rule_direction{
            PUBLISH,
            SUBSCRIBE,
            BOTH
        };
        rule_direction direction;
        std::string topic;
    };



    class user{
    public:
        user(const std::string & name, const std::string & pwd) : name(name),password(pwd){}
        user(const user & rhs) : name(rhs.name),password(rhs.password),rule(rhs.rule) { }
        user(user && rhs) : name(std::move(rhs.name)),password(std::move(rhs.password)),rule(std::move(rhs.rule)) {}

        user & operator=(const user & rhs){
            if(&rhs != this){
                name = rhs.name;
                password = rhs.password;
                rule = rhs.rule;
            }
            return *this;
        }

        user &operator=( user && rhs){
            if(&rhs != this){
                name = std::move(rhs.name);
                password = std::move(rhs.password);
                rule = std::move(rhs.rule);
            }
            return *this;
        }

        void set_access_rule(const pmq::rule & r){
            rule = r;
        }

        bool has_access(const std::string & topic )const{
            return true;
        }

    private:
        std::string name;
        std::string password;
    };
}

#endif //PMQ_USER_HPP
