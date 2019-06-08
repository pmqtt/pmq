//
// Created by Michael Burzan on 2019-05-26.
//

#ifndef PMQ_CONNECTOR_HPP
#define PMQ_CONNECTOR_HPP
#include <string>

namespace pmq{
    class connector{
    public:
        connector(const std::string & id);
        virtual ~connector();
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void reconnect() = 0;
        virtual bool is_connect() = 0;

        std::string  get_client_id()const{
            return this->client_id;
        }

    protected:
        std::string client_id;
    };

}

#endif //PMQ_CONNECTOR_HPP
