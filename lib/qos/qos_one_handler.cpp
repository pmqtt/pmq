//
// Created by pmqtt on 2019-07-06.
//

#include <lib/mqtt/mqtt_static_package.hpp>
#include "qos_one_handler.hpp"

void pmq::qos_one_handler::handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) {
    auto socket = msg->get_socket();
    pmq::mqtt_puback ack(socket);
    ack.send(msg->get_message_id());
}
