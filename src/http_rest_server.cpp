//
// Created by pmqtt on 2019-06-10.
//
#include <boost/log/trivial.hpp>
#include "header/http_rest_server.hpp"

namespace pmq{

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
        BOOST_LOG_TRIVIAL(debug) << "[ REST-API ] Recv message: "<< message.to_string();

        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        if (paths.empty())
        {
            BOOST_LOG_TRIVIAL(debug) << "REPLY STATUS OK " << " JSON: PMQ is running";
            message.reply(status_codes::OK, json::value::string(U("PMQ is running")));
            return;
        }

    }

    void http_rest_server::handle_post(http_request message){
        BOOST_LOG_TRIVIAL(debug)<<"HANDLE POST";
        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        if(!paths.empty()){
            BOOST_LOG_TRIVIAL(debug)<<"EXTRACT JSON";
            pplx::task<json::value> result = message.extract_json();
            result.wait();
            BOOST_LOG_TRIVIAL(debug)<<"EXTRACT JSON END";

            json::value value = result.get();
            BOOST_LOG_TRIVIAL(debug)<<"RESULT:"<<value;
            json::object obj = value.as_object();

            std::string user_name = obj.at("user").as_string();
            std::string user_pwd = obj.at("password").as_string();
            storage_service->add_user(user_name,user_pwd);
            BOOST_LOG_TRIVIAL(debug)<<" POST: user_name: "+ user_name << " pwd: "<<user_pwd;
            message.reply(status_codes::OK);
        }
        BOOST_LOG_TRIVIAL(debug)<<"HANDLE POST END";
    }
    void http_rest_server::handle_delete(http_request message){
    }
    void http_rest_server::handle_put(http_request message){
    }



    std::shared_ptr<http_rest_server> api_server;
    std::atomic_bool runLoop = true;
    void on_initialize(const string_t& address,std::shared_ptr<pmq::storage> & storage_service){
        uri_builder uri(address);
        uri.append_path(U("rest/api/v0.1/"));

        auto addr = uri.to_uri().to_string();
        api_server = std::shared_ptr<http_rest_server>(new http_rest_server(addr,storage_service));
        if(api_server) {
            api_server->open().wait();
            while (runLoop) {
                boost::this_thread::sleep_for(boost::chrono::seconds(1));
            }
            api_server->close().wait();
        }

    }
    void on_shutdown(){
        runLoop = false;

    }

}
