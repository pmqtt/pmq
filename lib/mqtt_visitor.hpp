//
// Created by PMQTT on 2019-04-14.
//

#ifndef PMQ_MQTT_VISITOR_HPP
#define PMQ_MQTT_VISITOR_HPP

namespace pmq{

    class mqtt_connect;
    class mqtt_publish;
    class mqtt_subscribe;
    template <pmq::u_int8 HEADER,pmq::u_int8 PAYLOAD_LENGTH> class mqtt_static_package;
    template <pmq::u_int8 HEADER,pmq::u_int8 PAYLOAD_LENGTH> class mqtt_controll_package;



    class mqtt_visitor{
    public:
        mqtt_visitor(){}
        virtual ~mqtt_visitor(){}

        virtual void visit(mqtt_connect * msg) = 0;
        virtual void visit(mqtt_publish * msg) = 0;
        virtual void visit(mqtt_subscribe * msg) = 0;
        virtual void visit(mqtt_static_package<192,0> * msg) = 0;
        virtual void visit(mqtt_static_package<208,0> * msg) = 0;
        virtual void visit(mqtt_static_package<224,0>  * msg) = 0;
        virtual void visit(mqtt_controll_package<112,2> * msg) = 0;
        virtual void visit(mqtt_controll_package<80,2> * msg) = 0;
        virtual void visit(mqtt_controll_package<98,2> * msg) = 0;
        virtual void visit(mqtt_controll_package<32,2> * msg) = 0;
        virtual void visit(mqtt_controll_package<176,2> * msg) = 0;
        virtual void visit(mqtt_controll_package<144,3> * msg) = 0;
        virtual void visit(mqtt_controll_package<64,2> * msg) = 0;

    };
}

#endif //PMQ_MQTT_VISITOR_HPP
