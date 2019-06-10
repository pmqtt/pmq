
#ifndef PMQ_STARTUP_CONFIGURATION_HPP
#define PMQ_STARTUP_CONFIGURATION_HPP
#include <cstdio>
namespace pmq{
    struct config{
    private:
        std::size_t port;
        std::size_t rest_port;
    public:
        constexpr config() : port(1883),rest_port(1884){}
        constexpr config(const config & rhs): port(rhs.port),rest_port(rhs.rest_port){
        }
        constexpr config & operator=(const config &rhs){
            if(this != &rhs) {
                this->port = rhs.port;
                this->rest_port = rhs.rest_port;
            }
            return *this;
        }

        constexpr void set_port(std::size_t port) { this->port = port;};
        constexpr void set_rest_port(std::size_t rest_port) { this->rest_port = rest_port;};

        constexpr std::size_t get_port()const{ return port;}
        constexpr std::size_t get_rest_port()const{ return rest_port;}

    };
}

#endif //PMQ_STARTUP_CONFIGURATION_HPP
