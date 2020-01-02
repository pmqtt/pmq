//
// Created by pmqtt on 2019-06-30.
//

#ifndef PMQ_REST_API_HPP
#define PMQ_REST_API_HPP
#include <string>
namespace pmq::rest{
    const std::string API_VERSION = "";
    const std::string URI = "rest/api/v0.1/";
    const std::string LOGIN = "login";

    const std::string CREATE_USER = "create_user";
    const std::string GET_WILL_MESSAGES = "get_will_messages";
    const std::string UPDATE_CLIENT_CONFIG = "update_client_config";

    const std::string CREATE_ACCESS = "create_access";

    const std::string JSON_CREATE_USER_USER_VALUE = "user";
    const std::string JSON_CREATE_USER_PASSWORD_VALUE = "password";

}

#endif //PMQ_REST_API_HPP
