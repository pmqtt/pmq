//
// Created by pmqtt on 2019-07-07.
//

#include "qos_two_handler.hpp"
#include "mqtt_static_package.hpp"
void pmq::qos_two_handler::handle(std::shared_ptr<pmq::storage> & storage,pmq::mqtt_publish *msg) {
    storage->save_qos_two_message_id(msg->get_message_id(),msg->get_client_id());
    auto socket = msg->get_socket();
    pmq::mqtt_pubrec pubrec(socket);
    pubrec.send(msg->get_message_id());
}
