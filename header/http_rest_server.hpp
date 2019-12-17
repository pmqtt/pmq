//
// Created by pmqtt on 2019-06-10.
//

#ifndef PMQ_HTTP_REST_SERVER_HPP
#define PMQ_HTTP_REST_SERVER_HPP

#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"

#include "header/storage.hpp"

#include <functional>
#include <map>


using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

namespace pmq {
    enum HTTP_METHOD_TYPE{
        GET,PUT,POST,DELETE
    };

    typedef std::function<void(http_request)> HTTP_REST_FUNC;
    typedef std::function<void(http_request,std::shared_ptr<pmq::storage>&)> HTTP_REST_FUNC_WITH_STORAGE_ACCESS;

    class http_rest_server {
    public:
        http_rest_server() = default;

        http_rest_server(utility::string_t url,const std::shared_ptr<pmq::storage> & storage_service);

        pplx::task<void> open() { return listener.open(); }

        pplx::task<void> close() { return listener.close(); }

        http_rest_server & add_router(){
            return *this;
        }
        http_rest_server & operator()(HTTP_METHOD_TYPE method_type, const std::string & route,const HTTP_REST_FUNC & method){
            auto &item = router_functions[method_type];
            item[route] = method;
            return *this;
        }
        http_rest_server & operator()(HTTP_METHOD_TYPE method_type, const std::string & route,const HTTP_REST_FUNC_WITH_STORAGE_ACCESS & method){
            auto &item = router_functions_with_storage[method_type];
            item[route] = method;
            return *this;
        }
        bool call_api(HTTP_METHOD_TYPE method_type,http_request message);
    private:
        void handle_get(http_request message);

        void handle_put(http_request message);

        void handle_post(http_request message);

        void handle_delete(http_request message);

    private:

        std::map<HTTP_METHOD_TYPE,std::map<std::string,HTTP_REST_FUNC>> router_functions;
        std::map<HTTP_METHOD_TYPE,std::map<std::string,HTTP_REST_FUNC_WITH_STORAGE_ACCESS>> router_functions_with_storage;
        http_listener listener;
        std::shared_ptr<pmq::storage> storage_service;
    };

    void on_initialize(const string_t& address,std::shared_ptr<pmq::storage> & storage_service);
    void on_shutdown();
    std::shared_ptr<http_rest_server> get_rest_server();

}


#endif //PMQ_HTTP_REST_SERVER_HPP
