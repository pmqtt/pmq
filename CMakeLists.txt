cmake_minimum_required(VERSION 3.9)
project(PMQ)
set(CMAKE_CXX_STANDARD 17)



find_package( Boost REQUIRED COMPONENTS system program_options thread date_time chrono unit_test_framework fiber log log_setup)
find_package( cpprestsdk REQUIRED)
find_package( OpenSSL REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories(${PROJECT_BINARY_DIR} ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} )



add_library(pmqtt STATIC lib/control_packet_type.hpp
        lib/mqtt_message.hpp lib/mqtt_types.hpp lib/mqtt_message.cpp
        lib/mqtt_package.cpp lib/mqtt_package.hpp lib/mqtt_connect.cpp lib/mqtt_connect.hpp
        lib/mqtt_publish.cpp lib/mqtt_publish.hpp lib/mqtt_static_package.hpp
        lib/mqtt_subscribe.cpp lib/mqtt_subscribe.hpp lib/pmqtt.hpp lib/mqtt_exception.hpp
        lib/mqtt_connection_info.hpp lib/mqtt_bad_header_exception.hpp lib/mqtt_visitor.hpp
        lib/subscriber.cpp lib/subscriber.hpp lib/connector.hpp lib/connector_mqtt311.hpp lib/connection_parameter.hpp lib/tls_socket.hpp)


add_executable(PMQ
                header/acceptor_exception.hpp
                header/bad_connection_exception.hpp
                header/config_exception.hpp
                src/main.cpp
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
                header/in_memory_storage.hpp src/in_memory_storage.cpp header/bad_connection_exception.hpp header/rest_api.hpp)

target_link_libraries(PMQ ${Boost_LIBRARIES} pmqtt cpprestsdk::cpprest)

