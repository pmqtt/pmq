//
// Created by pmqtt on 2019-06-29.
//

#ifndef A_PMQ_BAD_CONNECTION_EXCEPTION_HPP
#define A_PMQ_BAD_CONNECTION_EXCEPTION_HPP

#include <string>
namespace pmq::exception{
    class bad_connection_exception : public std::exception{
    public:
        explicit bad_connection_exception(std::string && msg) :msg(std::move(msg)) {

        }
        ~bad_connection_exception() override = default;
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}

#endif //PMQ_BAD_CONNECTION_EXCEPTION_HPP
