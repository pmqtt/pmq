//
// Created by pmqtt on 2019-07-19.
//

#ifndef __linux__
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE test_login_factory

#include <boost/test/included/unit_test.hpp>

#include "lib/server/login/login_factory.hpp"
#include "lib/server/login/login_handler.hpp"
#include "lib/server/login/login_allow_anonymous_handler.hpp"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}
BOOST_AUTO_TEST_CASE( CREATION_TEST )
{
    pmq::login_factory factory;
    std::shared_ptr<pmq::login_handler> need_login = factory.create(false);
    std::shared_ptr<pmq::login_handler> no_login_require = factory.create(true);
    BOOST_CHECK(instanceof<pmq::login_handler>(need_login.get()));
    BOOST_CHECK(instanceof<pmq::login_allow_anonymous_handler>(no_login_require.get()));
}


