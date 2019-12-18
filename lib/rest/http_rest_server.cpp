//
// Created by pmqtt on 2019-06-10.
//
#include <boost/log/trivial.hpp>
#include <thread>
#include <chrono>
#include "lib/rest/rest_api.hpp"
#include "http_rest_server.hpp"
#include "lib/rest/route_handler.hpp"



namespace pmq{


    http_rest_server::http_rest_server(utility::string_t url,const std::shared_ptr<pmq::storage> & storage_service)
        : listener(url), storage_service(storage_service)
    {

        listener.support(methods::GET, std::bind(&http_rest_server::handle_get, this, std::placeholders::_1));
        listener.support(methods::PUT, std::bind(&http_rest_server::handle_put, this, std::placeholders::_1));
        listener.support(methods::POST, std::bind(&http_rest_server::handle_post, this, std::placeholders::_1));
        listener.support(methods::DEL, std::bind(&http_rest_server::handle_delete, this, std::placeholders::_1));

    }

    bool http_rest_server::call_api(HTTP_METHOD_TYPE method_type,http_request message){
        auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
        std::string path = "/";
        if(!paths.empty()){
            path = paths[0];
        }
        if(router_functions.count(method_type) > 0){
            auto item = router_functions[method_type];
            if(item.count(path)>0){
                auto func = item[path];
                func(message);
                return true;
            }
        }
        if(router_functions_with_storage.count(method_type) > 0){
            auto item = router_functions_with_storage[method_type];
            if(item.count(path)>0){
                auto func = item[path];
                func(message,storage_service);
                return true;
            }
        }
        return false;
    }

    void http_rest_server::handle_get(http_request message){
        call_api(pmq::GET,message);
    }
    void http_rest_server::handle_post(http_request message){
        call_api(pmq::POST,message);
    }
    void http_rest_server::handle_delete(http_request message){
        call_api(pmq::DELETE,message);
    }
    void http_rest_server::handle_put(http_request message){
        call_api(pmq::DELETE,message);

    }



    std::shared_ptr<http_rest_server> api_server;
    std::atomic_bool runLoop = true;
    void on_initialize(const string_t& address,std::shared_ptr<pmq::storage> & storage_service){
        uri_builder uri(address);
        uri.append_path(U(pmq::rest::URI));

        auto addr = uri.to_uri().to_string();
        api_server = std::shared_ptr<http_rest_server>(new http_rest_server(addr,storage_service));
        pmq::init_route_handling();

        if(api_server) {
            api_server->open().wait();
            while (runLoop) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            api_server->close().wait();
        }
    }
    std::shared_ptr<http_rest_server> get_rest_server(){
        return api_server;
    }

    void on_shutdown(){
        runLoop = false;
    }

}
