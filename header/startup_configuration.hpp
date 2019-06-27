
#ifndef PMQ_STARTUP_CONFIGURATION_HPP
#define PMQ_STARTUP_CONFIGURATION_HPP
#include <cstdio>
#include <string>
namespace pmq{
    struct config{
    private:
        std::size_t port;
        std::size_t rest_port;
        std::array<bool,3> use_tls = {false,false,false};
        std::string cert_file="";
        std::string private_key_file="";
        std::string dh_file="";
    public:
        config() : port(1883),rest_port(1884) { }
        config(const config & rhs):
            port(rhs.port),
            rest_port(rhs.rest_port),
            use_tls(rhs.use_tls),
            cert_file(rhs.cert_file),
            private_key_file(rhs.private_key_file),
            dh_file(rhs.dh_file){
        }
        config & operator=(const config &rhs){
            if(this != &rhs) {
                this->port = rhs.port;
                this->rest_port = rhs.rest_port;
                this->use_tls = rhs.use_tls;
                this->cert_file = rhs.cert_file;
                this->private_key_file = rhs.private_key_file;
                this->dh_file = rhs.dh_file;
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

        bool should_use_tls()const{
            for(auto x : use_tls){
                if(!x) return false;
            }
            return true;
        }

    };
}

#endif //PMQ_STARTUP_CONFIGURATION_HPP
