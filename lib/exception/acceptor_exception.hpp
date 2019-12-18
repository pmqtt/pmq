//
// Created by pmqtt on 2019-06-28.
//

#ifndef PMQ_ACCEPTOR_EXCEPTION_HPP
#define PMQ_ACCEPTOR_EXCEPTION_HPP
#include <string>
namespace pmq::exception{
    class acceptor_exception : public std::exception{
    public:
        explicit acceptor_exception(std::string && msg) :msg(std::move(msg)) { }
        ~acceptor_exception() override = default;
        [[nodiscard]] const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}
#endif //PMQ_ACCEPTOR_EXCEPTION_HPP
