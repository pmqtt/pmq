#ifdef RESTAPI
//
// Created by pmqtt on 2019-08-04.
//

#ifndef PMQ_REST_HANDLER_HPP
#define PMQ_REST_HANDLER_HPP

#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"
using namespace web;
using namespace http;
using namespace utility;

namespace pmq{
    namespace rest{
        class rest_handler{
        public:
            rest_handler() = default;
            virtual ~rest_handler()= default;

            virtual void handle(http_request & message) = 0;
        };
    }
}

#endif //PMQ_REST_HANDLER_HPP
#endif