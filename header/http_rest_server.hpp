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

#include <map>


using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

namespace pmq {
    class http_rest_server {
    public:
        http_rest_server() = default;

        http_rest_server(utility::string_t url,const std::shared_ptr<pmq::storage> & storage_service);

        pplx::task<void> open() { return listener.open(); }

        pplx::task<void> close() { return listener.close(); }

    private:
        void handle_get(http_request message);

        void handle_put(http_request message);

        void handle_post(http_request message);

        void handle_delete(http_request message);

    private:

        http_listener listener;
        std::shared_ptr<pmq::storage> storage_service;
    };

    void on_initialize(const string_t& address,std::shared_ptr<pmq::storage> & storage_service);
    void on_shutdown();

}


#endif //PMQ_HTTP_REST_SERVER_HPP
