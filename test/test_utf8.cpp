//
// Created by pmqtt on 20.11.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_server

#include <boost/test/unit_test.hpp>

#include "lib/detail/utf8.hpp"

BOOST_AUTO_TEST_CASE( UTF8_VALIDATION_TEST )
{
    std::string buffer;
    buffer ="HALLO WELT";
    std::string end;
    end =0x03;
    buffer += end;
    buffer += " EIN WEITERER TEXT";

    BOOST_CHECK(!pmq::utf8::validate_utf8(buffer));
}