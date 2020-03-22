//
// Created by pmqtt on 22.03.20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_server_main

#include <boost/test/included/unit_test.hpp>

#include "lib/server/main.hpp"

BOOST_AUTO_TEST_CASE( test_create_client_creator )
{
    pmq::client_creator creator = create_client_creator();
    BOOST_CHECK_NO_THROW(auto x = creator.get("plain"));
    BOOST_CHECK_NO_THROW(auto y = creator.get("tls"));
    BOOST_CHECK_NO_THROW(auto z = creator.get("plain-tls"));
    try{
        auto x = creator.get("foo");
        BOOST_CHECK(false);
    }catch(const pmq::exception::config_exception & e){
        std::string excp_value = "foo doesn't configured for creator";
        BOOST_CHECK(e.what() == excp_value);
    }
}


