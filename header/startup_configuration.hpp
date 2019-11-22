
#ifndef PMQ_STARTUP_CONFIGURATION_HPP
#define PMQ_STARTUP_CONFIGURATION_HPP

#include <array>
#include <cstdio>
#include <string>
#include <header/config_module.hpp>
#include "config_exception.hpp"

namespace {
    void create_tls_config_exception(const std::array<bool,3> & tls_setted_params) {
        bool hasCertFile = tls_setted_params[0];
        bool hasKeyFile  = tls_setted_params[1];
        bool hasDHFile   = tls_setted_params[2];
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
        if(!hasCertFile && !hasKeyFile && hasDHFile){
            throw pmq::exception::config_exception(missing_cert_pk);
        }
        if(!hasCertFile && hasKeyFile && !hasDHFile){
            throw pmq::exception::config_exception(missing_cert_dh);
        }
        if(!hasCertFile && hasKeyFile && hasDHFile){
            throw pmq::exception::config_exception(missing_cert);
        }
        if(hasCertFile && !hasKeyFile && !hasDHFile){
            throw pmq::exception::config_exception(missing_pk_dh);
        }
        if(hasCertFile && !hasKeyFile && hasDHFile){
            throw pmq::exception::config_exception(missing_private_key);
        }
        if(hasCertFile && hasKeyFile && !hasDHFile){
            throw pmq::exception::config_exception(missing_diffie_hellman);
        }

    }
}

namespace pmq{
    struct config{
    private:
        std::size_t port;
        std::size_t rest_port;
        std::array<bool,3> use_tls = {false,false,false};
        std::string cert_file="";
        std::string private_key_file="";
        std::string dh_file="";
        bool allow_anonymous_login = true;
        pmq::config_module cfg;
    public:


    public:
        config() : port(1883),rest_port(1884) { }
        config(const config & rhs):
            port(rhs.port),
            rest_port(rhs.rest_port),
            use_tls(rhs.use_tls),
            cert_file(rhs.cert_file),
            private_key_file(rhs.private_key_file),
            dh_file(rhs.dh_file),allow_anonymous_login(rhs.allow_anonymous_login){
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
            }
            return *this;
        }

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
            if(should_use_tls()){
                return "TLS";
            }
            return "TCP";
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
        bool is_allow_anonymous_login() const {
            return allow_anonymous_login;
        }

        void set_allow_anonymous_login(bool allowAnonymousLogin) {
            allow_anonymous_login = allowAnonymousLogin;
        }

        void load_configuration_file(const std::string & filename);

        pmq::config_module get_client_config()const{
            return cfg;
        }

    };
}

pmq::config parse_program_options(int argc,char **argv);


#endif //PMQ_STARTUP_CONFIGURATION_HPP
