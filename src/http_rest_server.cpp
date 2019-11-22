//
// Created by pmqtt on 2019-06-10.
//
#include <boost/log/trivial.hpp>
#include <thread>
#include <chrono>
#include "header/rest_api.hpp"
#include "header/http_rest_server.hpp"



namespace pmq{
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
            BOOST_LOG_TRIVIAL(debug)<<"parsing error";
            return json::value::string(obj);
        }
    }

    http_rest_server::http_rest_server(utility::string_t url,const std::shared_ptr<pmq::storage> & storage_service)
        : listener(url), storage_service(storage_service)
    {

        listener.support(methods::GET, std::bind(&http_rest_server::handle_get, this, std::placeholders::_1));
        listener.support(methods::PUT, std::bind(&http_rest_server::handle_put, this, std::placeholders::_1));
        listener.support(methods::POST, std::bind(&http_rest_server::handle_post, this, std::placeholders::_1));
        listener.support(methods::DEL, std::bind(&http_rest_server::handle_delete, this, std::placeholders::_1));

    }

    void http_rest_server::handle_get(http_request message)
    {

        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        if (paths.empty())
        {
            message.reply(status_codes::OK, json::value::string(U("PMQ is running")));
            return;
        }else{

            if(paths[0] == pmq::rest::GET_WILL_MESSAGES){
                BOOST_LOG_TRIVIAL(debug)<<"PARSE WILL MESSAGE";
                message.reply(status_codes::OK,create_json_object_from_will_messages(storage_service));
            }
        }

    }

    void http_rest_server::handle_post(http_request message){
        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));


        if(paths.empty() == false && paths[0] == pmq::rest::CREATE_USER ){
            pplx::task<json::value> result = message.extract_json();
            result.wait();

            json::value value = result.get();
            json::object obj = value.as_object();

            std::string user_name = obj.at(pmq::rest::JSON_CREATE_USER_USER_VALUE).as_string();
            std::string user_pwd = obj.at(pmq::rest::JSON_CREATE_USER_PASSWORD_VALUE).as_string();

            storage_service->add_user( user_name, user_pwd);
            message.reply(status_codes::OK);
        }
    }
    void http_rest_server::handle_delete(http_request message){
    }
    void http_rest_server::handle_put(http_request message){
    }



    std::shared_ptr<http_rest_server> api_server;
    std::atomic_bool runLoop = true;
    void on_initialize(const string_t& address,std::shared_ptr<pmq::storage> & storage_service){
        uri_builder uri(address);
        uri.append_path(U(pmq::rest::URI));

        auto addr = uri.to_uri().to_string();
        api_server = std::shared_ptr<http_rest_server>(new http_rest_server(addr,storage_service));
        if(api_server) {
            api_server->open().wait();
            while (runLoop) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            api_server->close().wait();
        }

    }
    void on_shutdown(){
        runLoop = false;

    }

}
