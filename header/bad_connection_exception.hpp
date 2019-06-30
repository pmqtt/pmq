//
// Created by pmqtt on 2019-06-29.
//

#ifndef A_PMQ_BAD_CONNECTION_EXCEPTION_HPP
#define A_PMQ_BAD_CONNECTION_EXCEPTION_HPP

#include <string>
namespace pmq::exception{
    class bad_connection_exception : public std::exception{
    public:
        bad_connection_exception(const std::string & msg) :msg(msg) {

        }
        virtual ~bad_connection_exception() {

        }
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}

#endif //PMQ_BAD_CONNECTION_EXCEPTION_HPP
