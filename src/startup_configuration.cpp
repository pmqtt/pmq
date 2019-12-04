//
// Created by pmqtt on 2019-07-03.
//

#include <boost/program_options.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"

#include "header/PMQConfigure.hpp"
#include "header/startup_configuration.hpp"
#include "header/string.hpp"


pmq::config parse_program_options(int argc,char **argv){
    boost::program_options::options_description desc{"Options"};
    desc.add_options()
            ("help,h", "Help screen")
            ("version,v", "print version")
            ("config-file,c",boost::program_options::value<std::string>(),"Path to configuration file")
            ("port,p", boost::program_options::value<int>()->default_value(1883) ,"MQTT Broker port")
            ("rest-port,rp",boost::program_options::value<int>()->default_value(1884) ,"REST Interface port")
            ("tls-certificate",boost::program_options::value<std::string>(),"TLS certificate file")
            ("tls-private-key",boost::program_options::value<std::string>(),"TLS private key")
            ("tls-dh-file",boost::program_options::value<std::string>(),"Diffie-Hellman file")
            ("anonymous-login",boost::program_options::value<bool>()->default_value(true),"Allow or permit anoymous connection. Default is true")
            ("client-configuration-file",boost::program_options::value<std::string>(),"Path to client configuration")
            ;

    boost::program_options::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        exit(0);
    }
    if (vm.count("version")) {
        std::cout << "PMQ 2019 - v" << VERSION <<" - " <<std::endl;
        exit(0);
    }
    pmq::config conf;
    if(vm.count("config-file")){
        conf.load_from_file(vm["config-file"].as<std::string>());
    }
    if(vm.count("port")){
        conf.set_port(vm["port"].as<int>());
    }
    if(vm.count("rest-port")){
        conf.set_rest_port(vm["rest-port"].as<int>());
    }
    if(vm.count("tls-certificate")){
        conf.set_tls_cert_path(vm["tls-certificate"].as<std::string>());
    }
    if(vm.count("tls-private-key")){
        conf.set_tls_private_key(vm["tls-private-key"].as<std::string>());
    }
    if(vm.count("tls-dh-file")){
        conf.set_tls_dh_file(vm["tls-dh-file"].as<std::string>());
    }
    if(vm.count("anonymous-login")){
        conf.set_allow_anonymous_login(vm["anonymous-login"].as<bool>());
    }
    if(vm.count("client-configuration-file")){
        conf.load_client_configuration_file(vm["client-configuration-file"].as<std::string>());
    }


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
                    if(key == "port"){
                        this->set_port(std::atoi(value.c_str()));
                    }else if(key == "rest-port"){
                        this->set_rest_port(std::atoi(value.c_str()));
                    }else if(key == "anonymous-login"){
                        if(value == "true")
                            this->set_allow_anonymous_login(true);
                        else
                            this->set_allow_anonymous_login(false);
                    }else if(key == "tls-certificat"){
                        if(!value.empty())
                            this->set_tls_cert_path(value);
                    }else if(key == "tls-private-key"){
                        if(!value.empty())
                            this->set_tls_private_key(value);
                    }else if(key == "tls-dh-file"){
                        if(!value.empty())
                            this->set_tls_dh_file(value);
                    }else if(key == "client-configuration-file"){
                        if(!value.empty())
                            this->load_client_configuration_file(value);
                    }else if (key == "transformation-rule-file"){
                        if(!value.empty())
                            this->load_action_rule_file(value);
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