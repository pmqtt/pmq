//
// Created by pmqtt on 2019-06-15.
//

#ifndef PMQ_CLIENT_FACTORY_HPP
#define PMQ_CLIENT_FACTORY_HPP
#include <thread>
#include <functional>
#include "socket.hpp"
namespace pmq{
    class client_factory{
    public:
        client_factory() = default;
        virtual ~client_factory() = default;
        virtual std::shared_ptr<std::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> &  process)= 0;
    private:
    };


}


#endif //PMQ_CLIENT_FACTORY_HPP
