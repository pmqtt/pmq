//
// Created by PMQTT on 2019-03-03.
//

#ifndef PMQ_SERVER_HPP
#define PMQ_SERVER_HPP
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include <vector>


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

    class server : public pmq::mqtt_visitor {
    public:
        server(std::size_t port) :
            port(port),
            acceptor(io_context,tcp::endpoint(tcp::v4(),this->port)),
            should_service_run(true){
            this->server_info = std::make_shared<server_information>();
        }
        ~server();
        void run();

        void visit(mqtt_connect *msg) override;

        void visit(mqtt_publish *msg) override;

        void visit(mqtt_subscribe *msg) override;

        void visit(mqtt_static_package<192, 0> *msg) override;

        void visit(mqtt_static_package<208, 0> *msg) override;

        void visit(mqtt_static_package<224, 0> *msg) override;

        void visit(mqtt_controll_package<112, 2> *msg) override;

        void visit(mqtt_controll_package<80, 2> *msg) override;

        void visit(mqtt_controll_package<98, 2> *msg) override;

        void visit(mqtt_controll_package<32, 2> *msg) override;

        void visit(mqtt_controll_package<176, 2> *msg) override;

        void visit(mqtt_controll_package<144, 2> *msg) override;
        void visit(pmq::mqtt_puback *msg) override;

    private:
        void process(std::shared_ptr<pmq::socket> & socket);
        void clean_up(tcp::socket * socket);



    private:
        std::shared_ptr<server_information> server_info;
        boost::asio::io_context io_context;
        std::size_t port;
        tcp::acceptor acceptor;
        std::vector<std::shared_ptr<boost::thread>> client_threads;
        std::atomic_bool should_service_run;

    };
}


#endif //PMQ_SERVER_HPP
