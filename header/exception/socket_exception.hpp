//
// Created by PMQTT on 2019-03-28.
//

#ifndef PMQ_SOCKET_EXCEPTION_HPP
#define PMQ_SOCKET_EXCEPTION_HPP
#include <exception>
#include <string_view>
namespace pmq::exception{
    class socket_exception : public std::exception{
    public:
        socket_exception(const std::string_view & msg) :msg(msg) {

        }
        virtual ~socket_exception() {

        }
        virtual const char* what() const noexcept {
            return msg.data();
        }
    private:
        std::string_view msg;
    };
}

#endif //PMQ_SOCKET_EXCEPTION_HPP
