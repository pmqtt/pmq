//
// Created by pmqtt on 2019-07-21.
//

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "header/string.hpp"

std::vector <std::string> split(const std::string &str, const char *delim) {
    std::vector<std::string> splitted;
    boost::split(splitted, str, boost::is_any_of(delim));
    return splitted;
}

std::vector<std::string> pmq::detail::split_topic(const std::string &topic) {
    if(topic.length() == 0){ return std::vector<std::string>(); }
    bool is_first_sign_a_slash = false;
    if(topic[0] == '/'){
        is_first_sign_a_slash = true;
    }
    std::vector<std::string> splited = split(topic,"/");
    if( is_first_sign_a_slash ){
        splited.erase(splited.begin());
        splited[0] = "/"+splited[0];
    }
    if(splited[splited.size()-1].length() == 0){
        splited.pop_back();
    }
    return splited;
}


