//
// Created by pmqtt on 2019-06-28.
//

#ifndef PMQ_ACCEPTOR_EXCEPTION_HPP
#define PMQ_ACCEPTOR_EXCEPTION_HPP
#include <string>
namespace pmq::exception{
    class acceptor_exception : public std::exception{
    public:
        acceptor_exception(const std::string & msg) :msg(msg) {

        }
        virtual ~acceptor_exception() {

        }
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}
#endif //PMQ_ACCEPTOR_EXCEPTION_HPP
