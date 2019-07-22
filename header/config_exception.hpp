//
// Created by pmqtt on 2019-06-28.
//

#ifndef PMQ_CONFIG_EXCEPTION_HPP
#define PMQ_CONFIG_EXCEPTION_HPP
namespace pmq::exception{
    class config_exception : public std::exception{
    public:
        explicit  config_exception(const std::string & msg) :msg(msg) {}
        ~config_exception() override = default;
        const char* what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
}
#endif //PMQ_CONFIG_EXCEPTION_HPP
