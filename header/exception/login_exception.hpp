//
// Created by pmqtt on 02.12.19.
//

#ifndef PMQ_LOGIN_EXCEPTION_HPP
#define PMQ_LOGIN_EXCEPTION_HPP

#include <string>
namespace pmq::exception{
    class login_exception : public std::exception{
    public:
        explicit login_exception(std::string && msg) :msg(std::move(msg)) {}
        ~login_exception() override = default;
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}

#endif //PMQ_LOGIN_EXCEPTION_HPP
