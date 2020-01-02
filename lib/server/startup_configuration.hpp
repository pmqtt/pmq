
#ifndef PMQ_STARTUP_CONFIGURATION_HPP
#define PMQ_STARTUP_CONFIGURATION_HPP

#include <array>

#include <boost/program_options.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/log/trivial.hpp>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <lib/module/config_module.hpp>
#include <lib/exception/config_exception.hpp>
#include <lib/server/PMQConfigure.hpp>


namespace {
    void create_tls_config_exception(const std::array<bool, 3> &tls_setted_params) {
        bool hasCertFile = tls_setted_params[0];
        bool hasKeyFile = tls_setted_params[1];
        bool hasDHFile = tls_setted_params[2];
        std::string missing_diffie_hellman = "Missing Diffie-Hellman file - Certificate file and private key file was set - \n";
        missing_diffie_hellman += "\t To generate Diffie-Hellman file try this command \n";
        missing_diffie_hellman += "\t $> openssl dhparam -out dh2018.pem 2048";

        std::string missing_private_key = "Missing private key file - Certificate file and Diffie-Hellman file was set - \n";
        missing_private_key += "\t To generate private key file try this command \n";
        missing_private_key += "\t $> openssl genrsa -des3 -out server.key 1024";

        std::string missing_pk_dh = "Missing Diffie-Hellman file and private key file - Certificate file was set - \n";
        missing_pk_dh += "\t To generate Diffie-Hellman file try this command \n";
        missing_pk_dh += "\t $> openssl dhparam -out dh2018.pem 2048\n";
        missing_pk_dh += "\t To generate Diffie-Hellman file try this command \n";
        missing_pk_dh += "\t $> openssl genrsa -des3 -out server.key 1024";

        std::string missing_cert = "Missing certificate file - Private key file and Diffie-Hellman file was set - \n";
        missing_cert += "\t To generate Certificat file try this command \n";
        missing_cert += "\t $> openssl req -new -key server.key -out server.csr\n";
        missing_cert += "\t $> openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt";

        std::string missing_cert_pk = "Missing certificate file and Private key file -  Diffie-Hellman file was set - \n";
        missing_cert_pk += "\t To generate Certificat file try this command \n";
        missing_cert_pk += "\t $> openssl req -new -key server.key -out server.csr\n";
        missing_cert_pk += "\t $> openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt\n";
        missing_cert_pk += "\t To generate private key file try this command \n";
        missing_cert_pk += "\t $> openssl genrsa -des3 -out server.key 1024";

        std::string missing_cert_dh = "Missing certificate file and Diffie-Hellman file - Private key file was set - \n";
        missing_cert_dh += "\t To generate Certificat file try this command \n";
        missing_cert_dh += "\t $> openssl req -new -key server.key -out server.csr\n";
        missing_cert_dh += "\t $> openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt \n";
        missing_cert_dh += "\t To generate Diffie-Hellman file try this command \n";
        missing_cert_dh += "\t $> openssl genrsa -des3 -out server.key 1024";


        // c | k | d
        // 0  0  0  not used
        // 0  0  1  Missing certificate and private key     ok ok
        // 0  1  0  Missing certificate and diffie hellman  ok ok
        // 0  1  1  Missing certificate                     ok ok
        // 1  0  0  Missing private key and diffie hellman  ok ok
        // 1  0  1  Missing private key                     ok
        // 1  1  0  Missing diffie hellman                  ok
        // 1  1  1  not used
        if (!hasCertFile && !hasKeyFile && hasDHFile) {
            throw pmq::exception::config_exception(missing_cert_pk);
        }
        if (!hasCertFile && hasKeyFile && !hasDHFile) {
            throw pmq::exception::config_exception(missing_cert_dh);
        }
        if (!hasCertFile && hasKeyFile && hasDHFile) {
            throw pmq::exception::config_exception(missing_cert);
        }
        if (hasCertFile && !hasKeyFile && !hasDHFile) {
            throw pmq::exception::config_exception(missing_pk_dh);
        }
        if (hasCertFile && !hasKeyFile && hasDHFile) {
            throw pmq::exception::config_exception(missing_private_key);

            if (hasCertFile && hasKeyFile && !hasDHFile) {
                throw pmq::exception::config_exception(missing_diffie_hellman);
            }

        }
    }
}

namespace pmq{
    typedef std::function<void(const std::string &)> CONFIG_FUNC;
    enum CONNECTION_TYPE{
        PLAIN,
        TLS,
        PLAIN_TLS
    };
    struct config{
    private:
        CONNECTION_TYPE connection_type;
        std::size_t port;
        std::size_t rest_port;
        std::array<bool,3> use_tls = {false,false,false};
        std::string cert_file="";
        std::string private_key_file="";
        std::string dh_file="";
        std::string passphrase="";
        bool allow_anonymous_login = true;
        pmq::config_module cfg;
        bool client_certificate_as_username = false;
        std::vector<std::tuple<std::string,const boost::program_options::value_semantic*,std::string>> options;
        std::map<std::string,CONFIG_FUNC> callable;
        boost::program_options::options_description desc{"Options"};



    public:
        config() : port(1883),rest_port(1884) { }
        config(const config & rhs):
            connection_type(CONNECTION_TYPE::PLAIN),
            port(rhs.port),
            rest_port(rhs.rest_port),
            use_tls(rhs.use_tls),
            cert_file(rhs.cert_file),
            private_key_file(rhs.private_key_file),
            dh_file(rhs.dh_file),
            allow_anonymous_login(rhs.allow_anonymous_login),
            passphrase(rhs.passphrase),
            cfg(rhs.cfg),client_certificate_as_username(rhs.client_certificate_as_username){
        }
        config & operator=(const config &rhs){
            if(this != &rhs) {
                this->port = rhs.port;
                this->rest_port = rhs.rest_port;
                this->use_tls = rhs.use_tls;
                this->cert_file = rhs.cert_file;
                this->private_key_file = rhs.private_key_file;
                this->dh_file = rhs.dh_file;
                this->allow_anonymous_login = rhs.allow_anonymous_login;
                this->passphrase = rhs.passphrase;
                this->cfg = rhs.cfg;
                this->client_certificate_as_username = rhs.client_certificate_as_username;
            }
            return *this;
        }

        void print_version(const std::string & not_used){
            std::cout << "PMQ 2019 - v" << VERSION <<" - " <<std::endl;
            exit(0);
        }
        void print_help(const std::string & not_used){
            std::cout << desc << '\n';
            exit(0);
        }

        void load_from_file(const std::string & filename);

        void set_tls_cert_path(const std::string & cert_file){
            this->cert_file = cert_file;
            use_tls[0] = true;
        }
        void set_tls_private_key(const std::string & private_key_file){
            this->private_key_file = private_key_file;
            use_tls[1] = true;

        }
        void set_tls_dh_file(const std::string & dh_file){
            this->dh_file = dh_file;
            use_tls[2] = true;
        }


        constexpr void set_port(std::size_t port) { this->port = port;};
        constexpr void set_rest_port(std::size_t rest_port) { this->rest_port = rest_port;};

        constexpr std::size_t get_port()          const { return port;            }
        constexpr std::size_t get_rest_port()     const { return rest_port;       }
        std::string get_tls_cert_path()  const { return this->cert_file; }
        std::string get_tls_private_key()const { return this->private_key_file; }
        std::string get_tls_dh_file()    const { return this->dh_file; }

        std::string get_connection_type()const {
            switch (connection_type){
                case CONNECTION_TYPE::PLAIN: return "plain";
                case CONNECTION_TYPE::TLS:   return "tls";
                case CONNECTION_TYPE::PLAIN_TLS: return "plain-tls";
                default: return "none";
            }
        }

        bool should_use_tls()const{
            int k = 0;
            for(auto x : use_tls){
                if(x)
                    k++;
            }
            if( k == use_tls.size() ){
                return true;
            }
            if( k == 0 ){
                return false;
            }
            create_tls_config_exception(use_tls);
            return false; //should never call
        }

        void set_allowed_connection_type(const std::string & value){
            if( value == "plain"){
                connection_type = CONNECTION_TYPE::PLAIN;
            }
            else if (value == "tls" || value == "plain-tls" ){
                if( should_use_tls() ){
                    if(value == "plain-tls") {
                        connection_type = CONNECTION_TYPE::PLAIN_TLS;
                    }else {
                        connection_type = CONNECTION_TYPE::TLS;
                    }
                }
            }else{
                throw pmq::exception::config_exception("Unknow connection type "+value );
            }
        }

        void use_client_certificate_as_username(const std::string & value){
            BOOST_LOG_TRIVIAL(debug)<<"using client certificat as username : "<<value;
            if(value == "true" || value == "TRUE" || value == "True"){
                BOOST_LOG_TRIVIAL(debug)<<"set client_certificate_as_username: "<<value;
                client_certificate_as_username = true;
            }else{
                client_certificate_as_username = false;
            }
        }
        bool is_client_certificate_username()const{
            return client_certificate_as_username;
        }

        bool is_allow_anonymous_login() const {
            return allow_anonymous_login;
        }

        void set_allow_anonymous_login(bool allowAnonymousLogin) {
            allow_anonymous_login = allowAnonymousLogin;
        }
        void set_tls_certificate_passphrase(const std::string & pwd){
            passphrase = pwd;
        }
        std::string get_passphrase()const{
            return passphrase;
        }

        void load_client_configuration_file(const std::string & filename);
        void load_action_rule_file(const std::string & filename);

        const pmq::config_module & get_client_config()const{
            return cfg;
        }
    public:
        config & add_configuration(){
            return *this;
        }
        config & operator()(const std::string & name , const std::string &  description,const CONFIG_FUNC & invoke){
            std::vector<std::string> splittedString;
            boost::split(splittedString,name,boost::is_any_of(","));
            callable[splittedString[0]] = invoke;

            options.emplace_back(name, nullptr,description);

            return *this;
        }

        config& operator()(const std::string & name, const boost::program_options::value_semantic* s,const CONFIG_FUNC & invoke){
            std::vector<std::string> splittedString;
            boost::split(splittedString,name,boost::is_any_of(","));
            callable[splittedString[0]] = invoke;

            options.emplace_back(name, s , "");
            return *this;
        }

        config& operator()(const std::string& name, const boost::program_options::value_semantic* s, const std::string & description,const CONFIG_FUNC & invoke){
            std::vector<std::string> splittedString;
            boost::split(splittedString,name,boost::is_any_of(","));
            callable[splittedString[0]] = invoke;

            options.emplace_back(name, s,description);
            return *this;
        }

        void init_cli(std::size_t argc,char**argv){
            auto iter = desc.add_options();
            for(auto item: options){
                auto first = std::get<0>(item);
                auto second = std::get<1>(item);
                auto third = std::get<2>(item);
                if(second != nullptr){
                    if(third.empty()){
                        iter = iter(first.c_str(),second);
                    }else{
                        iter = iter(first.c_str(),second,third.c_str());
                    }
                }else{
                    iter = iter(first.c_str(),third.c_str());
                }

            }


            boost::program_options::variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            for(const auto &parameter : vm) {
                if (callable.count(parameter.first)) {
                    callable[parameter.first](parameter.second.as<std::string>());
                } else {
                    print_help("");
                }
            }

        }

    };
}

pmq::config parse_program_options(int argc,char **argv);


#endif //PMQ_STARTUP_CONFIGURATION_HPP
