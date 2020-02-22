//
// Created by pmqtt on 20.11.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_server
#include <boost/test/unit_test.hpp>

#include "lib/rest/http_rest_server.hpp"


#ifdef RESTAPI

http_request create_request(const std::string str){
    http_request request;
    uri_builder builder;
    builder.append_path_raw(str);
    request.set_request_uri(builder.to_uri());
    return request;
}

BOOST_AUTO_TEST_CASE( TEST_ADD_ROUTE )
{
    pmq::http_rest_server server;
    bool test = false;
    server.operator()(pmq::GET,"/",[&](http_request message){
        test = true;
    });

    server.call_api(pmq::GET,create_request(""));


    BOOST_CHECK(test);


}
BOOST_AUTO_TEST_CASE( TEST_ADD_ROUTES ) {
    pmq::http_rest_server server;
    bool t1 = false;
    bool t2 = false;
    bool t3 = false;
    server.add_router()
            (pmq::GET, "/", [&](http_request message) {
                t1 = true;
            })
            (pmq::GET, "get_will_message", [&](http_request message, std::shared_ptr<pmq::storage> &storage) {
                t2 = true;
            })
            (pmq::GET, "client_update", [&](http_request message) {
                t3 = true;
            });

    server.call_api(pmq::GET, create_request(""));
    server.call_api(pmq::GET, create_request("get_will_message"));
    server.call_api(pmq::GET, create_request("client_update"));


    BOOST_CHECK(t1 == t2 == t3 == true);

}
#else
BOOST_AUTO_TEST_CASE( DUMMY ){

}
#endif