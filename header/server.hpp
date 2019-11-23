//
// Created by PMQTT on 2019-03-03.
//

#ifndef PMQ_SERVER_HPP
#define PMQ_SERVER_HPP
#include <chrono>
#include <boost/asio.hpp>
#include <thread>
#include <boost/log/trivial.hpp>
#include <vector>

#include "header/client_factory.hpp"

#include "lib/control_packet_type.hpp"
#include "lib/mqtt_message.hpp"
#include "lib/mqtt_package.hpp"
#include "lib/mqtt_static_package.hpp"
#include "lib/mqtt_connection_info.hpp"
#include "lib/mqtt_visitor.hpp"
#include "lib/mqtt_publish.hpp"
#include "lib/mqtt_subscribe.hpp"
#include "lib/socket.hpp"


using boost::asio::ip::tcp;

namespace pmq{

    struct client_information{
        client_information(){
            connection_info = std::make_shared<pmq::mqtt_connection_info>();
        }
        client_information(const client_information & rhs){
            connected_at = rhs.connected_at;
            ip_adresse = rhs.ip_adresse;
            connection_info = rhs.connection_info;
        }
        client_information & operator=(const client_information & rhs){
            connected_at = rhs.connected_at;
            ip_adresse = rhs.ip_adresse;
            connection_info = rhs.connection_info;
            return *this;
        }
        std::chrono::system_clock::time_point connected_at;
        std::string ip_adresse;
        std::shared_ptr<pmq::mqtt_connection_info> connection_info;

    };

    struct server_information{
        std::chrono::system_clock::time_point server_started_at;
        std::vector<std::shared_ptr<client_information>> client_infos;
        std::size_t get_client_count()const { return client_infos.size(); }

        std::shared_ptr<client_information> add_new_client_info(){
            std::shared_ptr<client_information> client_info = std::make_shared<client_information>();
            this->client_infos.emplace_back(client_info);
            return client_info;
        }

        friend std::ostream& operator<< (std::ostream& stream, const server_information& sf) {
            stream<<"\tCount clients is : "<<sf.get_client_count()<<"\n";
            for(auto client_info : sf.client_infos) {
                stream << "\t\tClient is connected since : " <<"\n";
                stream << "\t\tWith ip address           : " <<client_info->ip_adresse<<"\n";
                stream << "\t\tWith client_id            : " <<client_info->connection_info->client_id<<"\n";
            }
            return stream;
        }

    };


    class server {
    public:
        explicit server(  std::shared_ptr< pmq::mqtt_visitor> & handler ) :
            should_service_run(true),
            handler(handler){
            this->server_info = std::make_shared<server_information>();
        }
        virtual ~server();

        virtual void run( std::shared_ptr<pmq::client_factory> & socket_factory );
        void process(std::shared_ptr<pmq::socket> & socket);



    private:
        void clean_up();

    private:
        std::atomic_bool should_service_run;
        std::shared_ptr< pmq::mqtt_visitor> handler;
        std::shared_ptr<server_information> server_info;
        std::vector<std::shared_ptr<std::thread>> client_threads;


    };
}


#endif //PMQ_SERVER_HPP
