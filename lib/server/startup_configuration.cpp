//
// Created by pmqtt on 2019-07-03.
//
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"

#include "lib/server/PMQConfigure.hpp"
#include "lib/server/startup_configuration.hpp"
#include "lib/detail/string.hpp"


pmq::config parse_program_options(int argc,char **argv){
    pmq::config conf;

    auto print_help = std::bind(&pmq::config::print_help,&conf, std::placeholders::_1);
    auto print_version = std::bind(&pmq::config::print_version,&conf, std::placeholders::_1);
    auto load_from_file = std::bind(&pmq::config::load_from_file,&conf, std::placeholders::_1);
    auto set_port = [&](const std::string & value){ conf.set_port(std::atoi(value.c_str())); };
    auto set_rest_port = [&](const std::string & value){ conf.set_rest_port(std::atoi(value.c_str())); };
    auto set_tls_certificate = std::bind(&pmq::config::set_tls_cert_path,&conf, std::placeholders::_1);;
    auto set_private_key = std::bind(&pmq::config::set_tls_private_key,&conf, std::placeholders::_1);
    auto set_dh_file = std::bind(&pmq::config::set_tls_dh_file,&conf, std::placeholders::_1);
    auto set_tls_passphrase = std::bind(&pmq::config::set_tls_certificate_passphrase,&conf, std::placeholders::_1);
    auto set_anonymous_login = [&](const std::string & value){ value=="true" ? conf.set_allow_anonymous_login(true) : conf.set_allow_anonymous_login(false); };
    auto load_client_configuration = std::bind(&pmq::config::load_client_configuration_file,&conf, std::placeholders::_1);;



    conf.add_configuration()("help,h", "Help screen",print_help)
            ("version,v", "print version",print_version)
            ("config-file,c",boost::program_options::value<std::string>(),"Path to configuration file",load_from_file)
            ("port,p", boost::program_options::value<std::string>()->default_value("1883") ,"MQTT Broker port",set_port)
            ("rest-port,rp",boost::program_options::value<std::string>()->default_value("1884") ,"REST Interface port",set_rest_port)
            ("tls-certificate",boost::program_options::value<std::string>(),"TLS certificate file",set_tls_certificate)
            ("tls-private-key",boost::program_options::value<std::string>(),"TLS private key",set_private_key)
            ("tls-dh-file",boost::program_options::value<std::string>(),"Diffie-Hellman file",set_dh_file)
            ("tls-certificate-passphrase",boost::program_options::value<std::string>(),"Passphrase to unlock certificate",set_tls_passphrase)
            ("anonymous-login",boost::program_options::value<std::string>()->default_value("true"),"Allow or permit anoymous connection. Default is true",set_anonymous_login)
            ("client-configuration-file",boost::program_options::value<std::string>(),"Path to client configuration",load_client_configuration)

            ;

    conf.init_cli(argc,argv);


    return conf;
}

std::string parse_node(const YAML::detail::iterator_value & node){
    std::string result = "{";
    for(auto item = node.second.begin(); item != node.second.end(); ++item){
        for(auto sub_item = item->begin(); sub_item != item->end(); ++sub_item) {
            std::string key = sub_item->first.Scalar();
            std::string value = sub_item->second.Scalar();
            result += pmq::detail::quote(key) + ":" + pmq::detail::quote(value) + ",";
        }
    }
    result.pop_back();
    result += "}";
    return result;

}


void pmq::config::load_from_file(const std::string & filename) {
    YAML::Node config = YAML::LoadFile(filename);
    for(const auto & node: config){
        if(node.first.Scalar() == "SERVER"){
            for(auto item = node.second.begin(); item != node.second.end(); ++item){
                for(auto sub_item = item->begin(); sub_item != item->end(); ++sub_item) {
                    std::string key = sub_item->first.Scalar();
                    std::string value = sub_item->second.Scalar();
                    if(callable.count(key)){
                        if(!value.empty()) {
                            callable[key](value);
                        }
                    }else{
                        BOOST_LOG_TRIVIAL(error)<<"Configuration error: Undefined key "<< key << " in "<<filename<<std::endl;
                    }
                }
            }
        }else{
            BOOST_LOG_TRIVIAL(error)<<"Configuration error: " + node.first.Scalar() + " not supported" ;
            break;
        }
    }
}

void pmq::config::load_client_configuration_file(const std::string &filename) {
    YAML::Node config = YAML::LoadFile(filename);
    std::map<std::string,std::string> general_config;
    std::map<std::string,std::string> specific_config;

    for(const auto & node : config){
        if(node.first.Scalar() == "GLOBAL"){
            this->cfg.set_global_config(parse_node(node));
        }else{
            std::string parent_key = node.first.Scalar();
            if(pmq::detail::split_topic(parent_key).size() == 1){
                general_config["$CONFIG_MODULE/"+parent_key] = parse_node(node);
            }else{
                specific_config["$CONFIG_MODULE/"+parent_key] = parse_node(node);
            }
        }
    }
    cfg.set_general_config(general_config);
    cfg.set_specific_config(specific_config);
}

void pmq::config::load_action_rule_file(const std::string & filename) {

}