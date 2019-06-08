//
// Created by Michael Burzan on 2019-05-26.
//

#ifndef PMQ_CONNECTOR_MQTT311_HPP
#define PMQ_CONNECTOR_MQTT311_HPP
#include "connector.hpp"

namespace pmq{
    class connector_mqtt311 : public pmq::connector{
    public:
        /*
         * Create a connection to a broker with standart parameter
         */
        connector_mqtt311(const std::string & id,const std::string broker_adr, std::size_t port);

        connector_mqtt311(const std::string & id,const std::shared_ptr<connection_parameter> & parameter);
        virtual ~connector_mqtt311();
        void connect() override ;
        void disconnect() override ;
        void reconnect() override;
        bool is_connect() override ;
    private:
        std::size_t port;
        std::string broker_adr;

    };
}

#endif //PMQ_CONNECTOR_MQTT311_HPP
