//
// Created by pmqtt on 2019-06-10.
//
#include <boost/log/trivial.hpp>

#include "header/rest_api.hpp"
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

        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        if (paths.empty())
        {
            message.reply(status_codes::OK, json::value::string(U("PMQ is running")));
            return;
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
                boost::this_thread::sleep_for(boost::chrono::seconds(1));
            }
            api_server->close().wait();
        }

    }
    void on_shutdown(){
        runLoop = false;

    }

}
