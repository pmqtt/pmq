cmake_minimum_required(VERSION 3.9)
project(PMQ)
set(CMAKE_CXX_STANDARD 17)



find_package( Boost REQUIRED COMPONENTS system program_options thread date_time chrono unit_test_framework fiber log log_setup)
find_package( cpprestsdk REQUIRED)
find_package( OpenSSL REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories(${PROJECT_BINARY_DIR} ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} )

add_library(pmqttclient STATIC client/messenger.cpp client/messenger.hpp)

add_library(pmqtt STATIC lib/control_packet_type.hpp
        lib/mqtt_message.hpp lib/mqtt_types.hpp lib/mqtt_message.cpp
        lib/mqtt_package.cpp lib/mqtt_package.hpp lib/mqtt_connect.cpp lib/mqtt_connect.hpp
        lib/mqtt_publish.cpp lib/mqtt_publish.hpp lib/mqtt_static_package.hpp
        lib/mqtt_subscribe.cpp lib/mqtt_subscribe.hpp lib/pmqtt.hpp lib/mqtt_exception.hpp
        lib/mqtt_connection_info.hpp lib/mqtt_bad_header_exception.hpp lib/mqtt_visitor.hpp
        lib/subscriber.cpp lib/subscriber.hpp lib/connector.hpp lib/connector_mqtt311.hpp
        lib/tls_socket.hpp lib/socket_functions.hpp lib/qos_handler.hpp lib/qos_zero_handler.cpp
        lib/qos_zero_handler.hpp lib/qos_one_handler.cpp lib/qos_one_handler.hpp lib/qos_two_handler.cpp
        lib/qos_two_handler.hpp lib/qos_handler_factory.cpp lib/qos_handler_factory.hpp lib/message.hpp
        lib/message.cpp lib/mqtt_types.cpp lib/mqtt_message_processor.hpp lib/mqtt_message_processor.cpp)



add_library(pmq_obj_lib OBJECT header/acceptor_exception.hpp
        header/bad_connection_exception.hpp
        header/config_exception.hpp
        src/server.cpp
        header/server.hpp
        header/null_deleter.hpp
        header/PMQConfigure.hpp
        header/security.hpp
        header/startup_configuration.hpp
        lib/socket.hpp
        header/socket_exception.hpp
        header/http_rest_server.hpp
        src/http_rest_server.cpp
        header/client_factory.hpp
        header/tcp_client_factory.hpp
        src/tcp_client_factory.cpp
        header/ssl_client_factory.hpp
        src/ssl_client_factory.cpp
        header/client_handler.hpp
        src/client_handler.cpp
        header/storage.hpp
        header/in_memory_storage.hpp
        src/in_memory_storage.cpp
        header/bad_connection_exception.hpp
        header/rest_api.hpp src/startup_configuration.cpp
        header/client_creator.hpp
        header/login_handler.hpp
        header/login_allow_anonymous_handler.hpp
        src/login_allow_anonymous_handler.cpp
        src/login_handler.cpp
        header/login_factory.hpp
        src/login_factory.cpp src/subscriber_container.cpp
        header/subscriber_container.hpp src/string.cpp
        header/subscriber_node.hpp
        src/subscriber_node.cpp
        header/string.hpp
        header/rest_handler.hpp)

add_executable(PMQ src/main.cpp $<TARGET_OBJECTS:pmq_obj_lib> )
target_link_libraries(PMQ ${Boost_LIBRARIES} pmqtt cpprestsdk::cpprest)

### TEST
include(CMakeFunctions/add_test_executable.txt)

add_test_executable(test_server test/test_server.cpp)
add_test_executable(test_login_handler test/test_login_handler.cpp)
add_test_executable(test_login_factory test/test_login_factory.cpp)
add_test_executable(test_subscriber_container test/test_subscriber_container.cpp)

