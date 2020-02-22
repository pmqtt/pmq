#ifdef RESTAPI
//
// Created by pmqtt on 17.12.19.
//
#include "route_handler.hpp"
#include "rest_api.hpp"
#include "http_rest_server.hpp"

std::string doube_quote(const std::string &str){
    std::string res = "\"";
    res += str;
    res += "\"";
    return res;
}

std::string create_json_client_will_message(const std::string & client_id, pmq::message & message){
    std::string client_id_str = doube_quote("client_id");
    std::string topic_str = doube_quote("topic");
    std::string message_str = doube_quote("message");

    std::string res = "";
    res += client_id_str +" : ";
    res += doube_quote(client_id) + ",";
    res += topic_str +" : ";
    res += doube_quote(message.get_topic()) +",";
    res += message_str +" : ";
    res += doube_quote(message.get_payload()) +" }";
    return res;
}


json::value create_json_object_from_will_messages(const std::shared_ptr<pmq::storage> & storage_service){
    std::string obj = "{ " + doube_quote("clients") +": [";
    std::map<std::string,pmq::message> will_message_map = storage_service->get_all_will_messages();
    std::size_t index = 0;
    for(auto p : will_message_map){
        obj += "{";
        if(index == will_message_map.size()-1){
            obj += create_json_client_will_message(p.first,p.second);
        }else{
            obj += create_json_client_will_message(p.first,p.second) +",";
        }
        index++;
    }
    obj += "]}";
    try {
        return json::value::parse(obj);
    }catch(...){
        BOOST_LOG_TRIVIAL(error)<<"JSON parse error: " + obj;
        return json::value::string(obj);
    }
}


void pmq::init_route_handling() {
    auto rest_server = pmq::get_rest_server();

    rest_server->add_router()
    ( pmq::GET,"/",[&](http_request message){
        message.reply(status_codes::OK, json::value::string(U("PMQ is running")));
    })
    ( pmq::GET,pmq::rest::GET_WILL_MESSAGES,[&](http_request message,std::shared_ptr<pmq::storage>& storage){
        message.reply(status_codes::OK,create_json_object_from_will_messages(storage));
    })
    ( pmq::GET,pmq::rest::UPDATE_CLIENT_CONFIG,[&](http_request message){
        message.reply(status_codes::OK);
    })
    ( pmq::POST,pmq::rest::CREATE_USER,[&](http_request message,std::shared_ptr<pmq::storage>& storage){
        pplx::task<json::value> result = message.extract_json();
        result.wait();

        json::value value = result.get();
        json::object obj = value.as_object();

        std::string user_name = obj.at(pmq::rest::JSON_CREATE_USER_USER_VALUE).as_string();
        std::string user_pwd = obj.at(pmq::rest::JSON_CREATE_USER_PASSWORD_VALUE).as_string();

        storage->add_user( user_name, user_pwd);
        message.reply(status_codes::OK);
    })

    ;


}
#endif