//
// Created by pmq on 05.01.20.
//

#ifndef PMQ_ACL_HPP
#define PMQ_ACL_HPP
#include <string>
#include <vector>
namespace pmq {
    namespace acl_module {
        enum acl_type {
            RULE,
            USERNAME,
            CLIENT_ID

        };

        enum rule_type {
            PUBLISH,
            SUBSCRIBE
        };
        enum access_type {
            ALLOW,
            DENY
        };
        enum flag_type {
            RETAINED
        };

        struct acl {
            std::string name;
            acl_type kind;
            std::vector<std::string> rules;
            std::vector<rule_type> types;
            std::string topic;
            access_type access;
            flag_type flag;
        };
    }
}
#endif //PMQ_ACL_HPP
