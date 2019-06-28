//
// Created by pmqtt on 2019-06-28.
//

#ifndef PMQ_TLS_HANDSHAKE_EXCEPTION_HPP
#define PMQ_TLS_HANDSHAKE_EXCEPTION_HPP
namespace pmq::exception{
    class tls_handshake_exception : public std::exception{
    public:
        tls_handshake_exception(const std::string_view & msg) :msg(msg) {

        }
        virtual ~tls_handshake_exception() {

        }
        virtual const char* what() const noexcept {
            return msg.data();
        }
    private:
        std::string_view msg;
    };
}
#endif //PMQ_TLS_HANDSHAKE_EXCEPTION_HPP
