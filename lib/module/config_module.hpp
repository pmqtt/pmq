//
// Created by pmqtt on 21.11.19.
//

#ifndef PMQ_CONFIG_MODULE_HPP
#define PMQ_CONFIG_MODULE_HPP
#include <map>
#include <string>
namespace pmq {
    class config_module {
    public:
        config_module() = default;
        virtual ~config_module() = default;
        config_module(const config_module & rhs )= default;
    public:
    private:
        std::string global_config;
    public:
        const std::string &get_global_config() const {
            return global_config;
        }

        void set_global_config(const std::string &globalConfig) {
            global_config = globalConfig;
        }

        std::map<std::string, std::string> &get_general_config() {
            return general_config;
        }

        void set_general_config(const std::map<std::string, std::string> &generalConfig) {
            general_config = generalConfig;
        }

        std::map<std::string, std::string> &get_specific_config()  {
            return specific_config;
        }

        void set_specific_config(const std::map<std::string, std::string> &specificConfig) {
            specific_config = specificConfig;
        }

    private:
        std::map<std::string,std::string> general_config;
        std::map<std::string,std::string> specific_config;
    };
}

#endif //PMQ_CONFIG_MODULE_HPP
