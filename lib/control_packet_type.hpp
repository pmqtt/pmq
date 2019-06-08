//
// Created by Michael Burzan on 2019-03-28.
//

#ifndef PMQ_CONTROL_PACKET_TYPE_HPP
#define PMQ_CONTROL_PACKET_TYPE_HPP
/************************
 * Name	Value	Direction of flow	        Description
 * Reserved	0	Forbidden	                Reserved
 * CONNECT	1	Client to Server	        Connection request
 * CONNACK	2	Server to Client	        Connect acknowledgment
 * PUBLISH	3	Client to Server or	        Publish message
		        Server to Client
 * PUBACK	4	Client to Server or	        Publish acknowledgment (QoS 1)
		        Server to Client
 * PUBREC	5	Client to Server or	        Publish received (QoS 2 delivery part 1)
		        Server to Client
 * PUBREL	6	Client to Server or	        Publish release (QoS 2 delivery part 2)
		        Server to Client
 * PUBCOMP	7	Client to Server or	        Publish complete (QoS 2 delivery part 3)
		        Server to Client
 * SUBSCRIBE 8	Client to Server	        Subscribe request
 * SUBACK	9	Server to Client	        Subscribe acknowledgment
 * UNSUBSCRIBE	10	Client to Server	    Unsubscribe request
 * UNSUBACK	11	Server to Client	        Unsubscribe acknowledgment
 * PINGREQ	12	Client to Server	        PING request
 * PINGRESP	13	Server to Client	        PING response
 * DISCONNECT	14	Client to Server or	    Disconnect notification
		            Server to Client
 * AUTH	    15	Client to Server or Server to Client	Authentication exchange
 *
 *
 ************************/


namespace pmq{
    enum CONTROL_PACKET_TYPE{
        CONNECT = 1,
        CONNACK = 2,
        PUBLISH,
        PUBACK,
        PUBREC,
        PUBREL,
        PUBCOMP,
        SUBSCRIBE,
        SUBACK,
        UNSUBSCRIPE,
        UNSUBACK,
        PINGRQ,
        PINGRESP,
        DISCONNECT,
        AUTH

    };
}
#endif //PMQ_CONTROL_PACKET_TYPE_HPP
