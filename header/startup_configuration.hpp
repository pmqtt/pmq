
#ifndef PMQ_STARTUP_CONFIGURATION_HPP
#define PMQ_STARTUP_CONFIGURATION_HPP
#include <cstdio>
namespace pmq{
    struct config{
    private:
        std::size_t port;
    public:
        constexpr config() : port(1883){}
        constexpr config(const config & rhs): port(rhs.port){
        }
        constexpr config & operator=(const config &rhs){
            if(this != &rhs) {
                this->port = rhs.port;
            }
            return *this;
        }

        constexpr void setPort(std::size_t port) { this->port = port;};
        constexpr std::size_t get_port()const{ return port;}

    };
}

#endif //PMQ_STARTUP_CONFIGURATION_HPP
