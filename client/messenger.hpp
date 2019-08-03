//
// Created by pmqtt on 2019-07-23.
//

#ifndef PMQ_MESSENGER_HPP
#define PMQ_MESSENGER_HPP
#include <string>
#include <iostream>
namespace pmq::client{

    /*HOW TO USE
     *
     * int main(int argc,char **argv){
     *  pmq::client::messenger messenger;
     *  messenger
     *      .set_broker_address("127.0.0.1",1883)
     *      .set_qos(1)
     *      .set_clean_session(true)
     *      .set_keep_alive(2);
     *
     *  messenger.subscribe("first/topic1");
     *
     *  messenger.publish("first/topic1","My first message");
     *  // blocked till received message from broker or a disconnect event was send
     *  std::pair<std::string,std::string> msg =  messenger.get_message();
     *  std::cout<<"Topic: "<< msg.first << "Payload:"<<msg.second<<std::endl;
     *
     *
     * }
     *
     */

    class messenger{
    public:
        messenger();
        ~messenger();

        //Fluent interface
        /*====================*/
        /**
         * @brief sets the qualaty of service for publish and subscribe
         * @param qos valid qos is 0,1 and 2
         * @throws qos_exception qos_exception will be thrown if qos > 2
         * @return messenger
         */
        messenger & set_qos(const std::size_t qos);
        /**
         *
         * @param address hostadress,ip4 or ipv6 adresse of the broker
         * @param port port number of the broker
         * @return messenger
         */
        messenger & set_broker_address(const std::string & address ,std::size_t port);
        /**
         *
         * @param address adress in mqtt uri style e.g mqtt://host:1883
         * throws uri_format_exception uri_format_exception will be thrown if address ill formated uri
         * @return messenger
         */
        messenger & set_broker_address(const std::string & address);

        messenger & set_keep_alive(std::size_t sec);
        messenger & set_clean_session(bool clean);


        void connect();
        void connect(const std::string &host,std::size_t port);
        void connect_infinity();

        void subscribe(const std::string & topic);
        void publish(const std::string & topic,const std::string & payload);
        std::pair<std::string,std::string> get_message();
    private:
        std::size_t qos;
        std::size_t pos;
        std::string address;
        std::size_t keep_alive_interval;
        bool clean_session;

    };
}

#endif //PMQ_MESSENGER_HPP
