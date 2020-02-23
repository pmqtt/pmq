cmake_minimum_required(VERSION 3.9)
project(PMQ)
set(CMAKE_CXX_STANDARD 17)

message(HALLO WELT)


add_definitions(-DRESTAPI )
if(APPLE)
    add_definitions(-DBOOST_LOG_DYN_LINK)
else()
    add_definitions(-DBOOST_LOG_DYN_LINK)
endif()


find_package( Boost REQUIRED COMPONENTS system program_options unit_test_framework log )
find_package( cpprestsdk REQUIRED )
find_package( OpenSSL REQUIRED )
if(OPENSSL_FOUND)
    if(APPLE)
        include_directories(/usr/local/Cellar/openssl/1.1.1d/include)
        list(APPEND LIB_LIST /usr/local/Cellar/openssl/1.1.1d/lib/libssl.dylib)
        list(APPEND LIB_LIST /usr/local/Cellar/openssl/1.1.1d/lib/libcrypto.dylib)
        message(STATUS  " APPLE OpenSSL Version:${OPENSSL_LIBRARIES}  ${OPENSSL_INCLUDE_DIR} ${LIB_LIST}")
    else()
        include_directories(${OPENSSL_INCLUDE_DIR})
        list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    endif()
endif()
find_package( yaml-cpp REQUIRED )

if(yaml-cpp_FOUND)
    if(NOT DEFINED ${YAML_CPP_LIBRARIES})
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(YAML_CPP_LIBRARIES /usr/local/lib/libyaml-cpp.a)
        endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        if( EXISTS "/usr/local/lib64/libyaml-cpp.a")
            set(YAML_CPP_LIBRARIES /usr/local/lib64/libyaml-cpp.a)
        else(EXISTS "/usr/local/lib64/libyaml-cpp.a")
            if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
                set(YAML_CPP_LIBRARIES /usr/local/lib/libyaml-cpp.a)
            endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        endif(EXISTS "/usr/local/lib64/libyaml-cpp.a")
    endif(NOT DEFINED ${YAML_CPP_LIBRARIES})
endif(yaml-cpp_FOUND)



include_directories(${PROJECT_BINARY_DIR} ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS}   )

add_library(pmqttclient STATIC lib/client_api/messenger.cpp lib/client_api/messenger.hpp)

add_library(pmqtt STATIC lib/mqtt/control_packet_type.hpp
        lib/mqtt/mqtt_message.hpp lib/mqtt/mqtt_types.hpp lib/mqtt/mqtt_message.cpp
        lib/mqtt/mqtt_package.cpp lib/mqtt/mqtt_package.hpp lib/mqtt/mqtt_connect.cpp lib/mqtt/mqtt_connect.hpp
        lib/mqtt/mqtt_publish.cpp lib/mqtt/mqtt_publish.hpp lib/mqtt/mqtt_static_package.hpp
        lib/mqtt/mqtt_subscribe.cpp lib/mqtt/mqtt_subscribe.hpp lib/mqtt/pmqtt.hpp lib/exception/mqtt_exception.hpp
        lib/mqtt/mqtt_connection_info.hpp lib/exception/mqtt_bad_header_exception.hpp lib/mqtt/mqtt_visitor.hpp
        lib/container/subscriber.cpp lib/container/subscriber.hpp
        lib/network/tls_socket.hpp lib/network/socket_functions.hpp lib/qos/qos_handler.hpp lib/qos/qos_zero_handler.cpp
        lib/qos/qos_zero_handler.hpp lib/qos/qos_one_handler.cpp lib/qos/qos_one_handler.hpp lib/qos/qos_two_handler.cpp
        lib/qos/qos_two_handler.hpp lib/qos/qos_handler_factory.cpp lib/qos/qos_handler_factory.hpp lib/mqtt/message.hpp
        lib/mqtt/message.cpp lib/mqtt/mqtt_types.cpp lib/detail/mqtt_message_processor.hpp lib/detail/mqtt_message_processor.cpp lib/detail/utf8.hpp lib/exception/login_exception.hpp)



add_library(pmq_obj_lib OBJECT lib/exception/acceptor_exception.hpp
        lib/exception/bad_connection_exception.hpp
        lib/exception/config_exception.hpp
        lib/server/server.cpp
        lib/server/server.hpp
        lib/server/null_deleter.hpp
        lib/server/PMQConfigure.hpp
        lib/server/security.hpp
        lib/server/startup_configuration.hpp
        lib/network/socket.hpp
        lib/exception/socket_exception.hpp
        lib/rest/http_rest_server.hpp
        lib/rest/http_rest_server.cpp
        lib/network/client_factory.hpp
        lib/network/tcp_client_factory.hpp
        lib/network/tcp_client_factory.cpp
        lib/network/ssl_client_factory.hpp
        lib/network/ssl_client_factory.cpp
        lib/network/connection_factory.hpp
        lib/server/client_handler.hpp
        lib/server/client_handler.cpp
        lib/storage/storage.hpp
        lib/storage/in_memory_storage.hpp
        lib/storage/in_memory_storage.cpp
        lib/exception/bad_connection_exception.hpp
        lib/rest/rest_api.hpp lib/server/startup_configuration.cpp
        lib/server/client_creator.hpp
        lib/server/login/login_handler.hpp
        lib/server/login/login_allow_anonymous_handler.hpp
        lib/server/login/login_allow_anonymous_handler.cpp
        lib/server/login/login_handler.cpp
        lib/server/login/login_factory.hpp
        lib/server/login/login_factory.cpp
        lib/container/subscriber_container.cpp
        lib/container/subscriber_container.hpp
        lib/detail/string.cpp
        lib/container/subscriber_node.hpp
        lib/container/subscriber_node.cpp
        lib/detail/string.hpp
        lib/rest/rest_handler.hpp
        lib/rest/route_handler.hpp
        lib/rest/route_handler.cpp
        lib/module/config_module.hpp
        lib/module/transformation_module.hpp
        lib/module/transformation_identity.hpp)

add_executable(PMQ src/main.cpp $<TARGET_OBJECTS:pmq_obj_lib> )
target_link_libraries(PMQ  ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES} pmqtt cpprestsdk::cpprest ${LIB_LIST} )

### TEST
include(CMakeFunctions/add_test_executable.txt)

add_test_executable(test_server test/test_server.cpp)
add_test_executable(test_login_handler test/test_login_handler.cpp)
add_test_executable(test_login_factory test/test_login_factory.cpp)
add_test_executable(test_subscriber_container test/test_subscriber_container.cpp)
add_test_executable(test_utf8 test/test_utf8.cpp)
add_test_executable(test_http_rest_server test/test_http_rest_server.cpp)


### install
install(TARGETS PMQ EXPORT PMQ RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "7")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-all")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "pmqtt")
set(CPACK_PACKAGE_DESCRIPTION "MQTT Message Broker")

include(CPack)