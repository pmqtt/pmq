//
// Created by pmqtt on 2019-07-21.
//

#ifndef PMQ_STRING_HPP
#define PMQ_STRING_HPP
#include <string>
#include <vector>

namespace pmq::detail {
    std::vector <std::string> split_topic(const std::string &topic);
    bool topic_start_with(const std::string & topic,const std::string & begins);
    std::string quote(const std::string & str);
}

#endif //PMQ_STRING_HPP
