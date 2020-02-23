//
// Created by pmqtt on 2019-07-08.
//
#ifndef __linux__
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE test_subscriber_container

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <lib/network/socket.hpp>
#include <lib/container/subscriber.hpp>
#include "lib/detail/string.hpp"
#include "lib/container/subscriber_container.hpp"

BOOST_AUTO_TEST_CASE( split_topic_test)
{
    std::vector<std::string> result = pmq::detail::split_topic("a/b/c/d/e");

    BOOST_CHECK(result[0] == "a");
    BOOST_CHECK(result[1] == "b");
    BOOST_CHECK(result[2] == "c");
    BOOST_CHECK(result[3] == "d");
    BOOST_CHECK(result[4] == "e");

    std::vector<std::string> test_res = pmq::detail::split_topic("a");
    BOOST_CHECK(test_res[0] == "a");

    std::vector<std::string> test_res2 = pmq::detail::split_topic("a/");
    BOOST_CHECK(test_res2[0] == "a");

    std::vector<std::string> test_res3 = pmq::detail::split_topic("/a/b");
    BOOST_CHECK(test_res3[0] == "/a");



}

BOOST_AUTO_TEST_CASE( subscriber_node_constructor_test )
{
    pmq::detail::subscriber_node node("a");
    BOOST_CHECK(node.get_sub_topic() == "a");
}

BOOST_AUTO_TEST_CASE( subscriber_node_get_all_wildcard_subscriber_test )
{
    pmq::detail::subscriber_node node("a");
    std::shared_ptr<pmq::socket> socket;
    auto sub1 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"test/a",0);

    node.add_subscriber(sub1,false);
    node.add_subscriber(sub2,true);
    node.add_subscriber(sub3,false);
    std::vector<std::shared_ptr<pmq::subscriber>> res = node.get_all_wildcard_subscriber();
    BOOST_CHECK(res[0].get() == sub2.get());
}


BOOST_AUTO_TEST_CASE( subscriber_node_remove_subscriber )
{
    pmq::detail::subscriber_node node("a");
    std::shared_ptr<pmq::socket> socket;
    auto sub1 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"test/a",0);

    node.add_subscriber(sub1,false);
    node.add_subscriber(sub2,true);
    node.add_subscriber(sub3,false);
    node.remove_subscriber(sub2);
    std::vector<std::shared_ptr<pmq::subscriber>> res = node.get_subscribers();
    BOOST_CHECK(res[0].get() == sub1.get());
    BOOST_CHECK(res[1].get() == sub3.get());
    BOOST_CHECK( sub3 );

}


BOOST_AUTO_TEST_CASE( subscriber_node_get_subscribers_test )
{
    pmq::detail::subscriber_node node("a");
    std::shared_ptr<pmq::socket> socket;
    auto sub1 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"test/a",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"test/a",0);

    node.add_subscriber(sub1,false);
    node.add_subscriber(sub2,true);
    node.add_subscriber(sub3,false);
    std::vector<std::shared_ptr<pmq::subscriber>> res = node.get_subscribers();
    BOOST_CHECK(res[0].get() == sub1.get());
    BOOST_CHECK(res[1].get() == sub2.get());
    BOOST_CHECK(res[2].get() == sub3.get());
}


BOOST_AUTO_TEST_CASE( subscriber_container_constructor_test )
{
    pmq::detail::subscriber_container container;
    BOOST_CHECK(container.get_size() == 0);
}

BOOST_AUTO_TEST_CASE( subscriber_container_toplevel_wildcard_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"#",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"#",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"#",0);
    container.insert_subscriber(sub1,"#");
    container.insert_subscriber(sub2,"#");
    container.insert_subscriber(sub3,"#");
    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("#");
    BOOST_CHECK(result.size() == 3);
    BOOST_CHECK(result[0].get() == sub1.get());
    BOOST_CHECK(result[1].get() == sub2.get());
    BOOST_CHECK(result[2].get() == sub3.get());
}

BOOST_AUTO_TEST_CASE( subscriber_container_toplevel_wildcard_two_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"#",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"#",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"#",0);
    container.insert_subscriber(sub1,"#");
    container.insert_subscriber(sub2,"#");
    container.insert_subscriber(sub3,"#");
    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a");
    BOOST_CHECK(result.size() == 3);
    BOOST_CHECK(result[0].get() == sub1.get());
    BOOST_CHECK(result[1].get() == sub2.get());
    BOOST_CHECK(result[2].get() == sub3.get());
}


BOOST_AUTO_TEST_CASE( subscriber_container_one_level_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"b",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"c",0);
    container.insert_subscriber(sub1,"a");
    container.insert_subscriber(sub2,"b");
    container.insert_subscriber(sub3,"c");
    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a");
    BOOST_CHECK(result[0].get() == sub1.get());
    result = container.get_subscriber("b");
    BOOST_CHECK(result[0].get() == sub2.get());
    result = container.get_subscriber("c");
    BOOST_CHECK(result[0].get() == sub3.get());
}

BOOST_AUTO_TEST_CASE( subscriber_container_same_level_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"b",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"c",0);
    container.insert_subscriber(sub1,"a");
    container.insert_subscriber(sub2,"a");
    container.insert_subscriber(sub3,"a");
    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a");
    BOOST_CHECK(result.size() == 3);
}


BOOST_AUTO_TEST_CASE( subscriber_container_multi_level_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a/b/c");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub1.get());

    result = container.get_subscriber("a/b");
    BOOST_CHECK(result.size() == 0);

    result = container.get_subscriber("a/b/d");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub2.get());

    result = container.get_subscriber("a/b/e");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub3.get());
}

BOOST_AUTO_TEST_CASE( subscriber_container_multi_level_wildcard_level_one_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"#",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    container.insert_subscriber(sub4,"#");

    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a/b/c");
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub1.get());

    result = container.get_subscriber("a/b");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub4.get());

    result = container.get_subscriber("a/b/d");
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub2.get());

    result = container.get_subscriber("a/b/e");
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub3.get());
}

BOOST_AUTO_TEST_CASE( subscriber_container_multi_level_wildcard_level_last_test)
{
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"a/b/#",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    container.insert_subscriber(sub4,"a/b/#");

    std::vector<std::shared_ptr<pmq::subscriber>> result = container.get_subscriber("a/b/c");
    std::cout <<result.size()<<std::endl;
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub1.get());


    result = container.get_subscriber("a/b/d");
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub2.get());

    result = container.get_subscriber("a/b/e");
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub4.get());
    BOOST_CHECK(result[1].get() == sub3.get());
}

BOOST_AUTO_TEST_CASE( subscriber_container_multi_level_wildcard_predeccor_level_test)
{
    std::cout<<"Test subscriber container multi level test"<<std::endl;
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"a/b/#",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    std::cout<<"START"<<std::endl;
    container.insert_subscriber(sub4,"a/b/#");

    auto result = container.get_subscriber("a/b/i");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub4.get());

}

BOOST_AUTO_TEST_CASE( subscriber_container_multi_level_wildcard_predeccor_level_two_test)
{
    std::cout<<"Test subscriber container multi level test"<<std::endl;
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"a/b/#",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    std::cout<<"START"<<std::endl;
    container.insert_subscriber(sub4,"a/b/#");

    auto result = container.get_subscriber("a/b");
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub4.get());

}

BOOST_AUTO_TEST_CASE( subscriber_container_single_level_test)
{
    std::cout<<"Test subscriber container single level test"<<std::endl;
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/b/c",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/b/d",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/b/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"a/+/e",0);
    container.insert_subscriber(sub1,"a/b/c");
    container.insert_subscriber(sub2,"a/b/d");
    container.insert_subscriber(sub3,"a/b/e");
    std::cout<<"START"<<std::endl;
    container.insert_subscriber(sub4,"a/+/e");

    auto result = container.get_subscriber("a/b/e");
    std::cout<<"size:"<<result.size()<<std::endl;
    BOOST_CHECK(result.size() == 2);
    BOOST_CHECK(result[0].get() == sub3.get());
    BOOST_CHECK(result[1].get() == sub4.get());

}

BOOST_AUTO_TEST_CASE( subscriber_container_single_level_deep_test)
{
    std::cout<<"Test subscriber container single level test"<<std::endl;
    pmq::detail::subscriber_container container;
    std::shared_ptr<pmq::socket> socket;

    auto sub1 = std::make_shared<pmq::subscriber>(socket,"a/u/e",0);
    auto sub2 = std::make_shared<pmq::subscriber>(socket,"a/i/e",0);
    auto sub3 = std::make_shared<pmq::subscriber>(socket,"a/g/e",0);
    auto sub4 = std::make_shared<pmq::subscriber>(socket,"a/+/e",0);

    auto sub5 = std::make_shared<pmq::subscriber>(socket,"a/+/e/f/g/h/i",0);
    container.insert_subscriber(sub1,"a/u/e");
    container.insert_subscriber(sub2,"a/i/e");
    container.insert_subscriber(sub3,"a/g/e");
    container.insert_subscriber(sub5,"a/b/e/f/g/h/i");

    container.insert_subscriber(sub4,"a/+/e/f/g/h/i");

    auto result = container.get_subscriber("a/c/e/f/g/h/i");
    std::cout<<"size:"<<result.size()<<std::endl;
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result[0].get() == sub4.get());

}

