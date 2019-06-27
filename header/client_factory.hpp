//
// Created by pmqtt on 2019-06-15.
//

#ifndef PMQ_CLIENT_FACTORY_HPP
#define PMQ_CLIENT_FACTORY_HPP
#include <boost/thread.hpp>
#include <functional>
#include <lib/socket.hpp>
namespace pmq{
    class client_factory{
    public:
        client_factory(){}
        virtual ~client_factory(){}
        virtual std::shared_ptr<boost::thread> create_client_thread( std::function< void(std::shared_ptr<socket>&)> &  process)= 0;
    private:
    };
}


#endif //PMQ_CLIENT_FACTORY_HPP
