# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cefour/Projects/pmq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cefour/Projects/pmq

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/cefour/Projects/pmq/CMakeFiles /Users/cefour/Projects/pmq/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/cefour/Projects/pmq/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test_subscriber_container

# Build rule for target.
test_subscriber_container: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_subscriber_container
.PHONY : test_subscriber_container

# fast build rule for target.
test_subscriber_container/fast:
	$(MAKE) -f CMakeFiles/test_subscriber_container.dir/build.make CMakeFiles/test_subscriber_container.dir/build
.PHONY : test_subscriber_container/fast

#=============================================================================
# Target rules for targets named test_login_factory

# Build rule for target.
test_login_factory: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_login_factory
.PHONY : test_login_factory

# fast build rule for target.
test_login_factory/fast:
	$(MAKE) -f CMakeFiles/test_login_factory.dir/build.make CMakeFiles/test_login_factory.dir/build
.PHONY : test_login_factory/fast

#=============================================================================
# Target rules for targets named PMQ

# Build rule for target.
PMQ: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PMQ
.PHONY : PMQ

# fast build rule for target.
PMQ/fast:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/build
.PHONY : PMQ/fast

#=============================================================================
# Target rules for targets named pmq_obj_lib

# Build rule for target.
pmq_obj_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pmq_obj_lib
.PHONY : pmq_obj_lib

# fast build rule for target.
pmq_obj_lib/fast:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/build
.PHONY : pmq_obj_lib/fast

#=============================================================================
# Target rules for targets named test_server

# Build rule for target.
test_server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_server
.PHONY : test_server

# fast build rule for target.
test_server/fast:
	$(MAKE) -f CMakeFiles/test_server.dir/build.make CMakeFiles/test_server.dir/build
.PHONY : test_server/fast

#=============================================================================
# Target rules for targets named pmqtt

# Build rule for target.
pmqtt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pmqtt
.PHONY : pmqtt

# fast build rule for target.
pmqtt/fast:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/build
.PHONY : pmqtt/fast

#=============================================================================
# Target rules for targets named test_login_handler

# Build rule for target.
test_login_handler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_login_handler
.PHONY : test_login_handler

# fast build rule for target.
test_login_handler/fast:
	$(MAKE) -f CMakeFiles/test_login_handler.dir/build.make CMakeFiles/test_login_handler.dir/build
.PHONY : test_login_handler/fast

#=============================================================================
# Target rules for targets named pmqttclient

# Build rule for target.
pmqttclient: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pmqttclient
.PHONY : pmqttclient

# fast build rule for target.
pmqttclient/fast:
	$(MAKE) -f CMakeFiles/pmqttclient.dir/build.make CMakeFiles/pmqttclient.dir/build
.PHONY : pmqttclient/fast

client/messenger.o: client/messenger.cpp.o

.PHONY : client/messenger.o

# target to build an object file
client/messenger.cpp.o:
	$(MAKE) -f CMakeFiles/pmqttclient.dir/build.make CMakeFiles/pmqttclient.dir/client/messenger.cpp.o
.PHONY : client/messenger.cpp.o

client/messenger.i: client/messenger.cpp.i

.PHONY : client/messenger.i

# target to preprocess a source file
client/messenger.cpp.i:
	$(MAKE) -f CMakeFiles/pmqttclient.dir/build.make CMakeFiles/pmqttclient.dir/client/messenger.cpp.i
.PHONY : client/messenger.cpp.i

client/messenger.s: client/messenger.cpp.s

.PHONY : client/messenger.s

# target to generate assembly for a file
client/messenger.cpp.s:
	$(MAKE) -f CMakeFiles/pmqttclient.dir/build.make CMakeFiles/pmqttclient.dir/client/messenger.cpp.s
.PHONY : client/messenger.cpp.s

lib/message.o: lib/message.cpp.o

.PHONY : lib/message.o

# target to build an object file
lib/message.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/message.cpp.o
.PHONY : lib/message.cpp.o

lib/message.i: lib/message.cpp.i

.PHONY : lib/message.i

# target to preprocess a source file
lib/message.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/message.cpp.i
.PHONY : lib/message.cpp.i

lib/message.s: lib/message.cpp.s

.PHONY : lib/message.s

# target to generate assembly for a file
lib/message.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/message.cpp.s
.PHONY : lib/message.cpp.s

lib/mqtt_connect.o: lib/mqtt_connect.cpp.o

.PHONY : lib/mqtt_connect.o

# target to build an object file
lib/mqtt_connect.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_connect.cpp.o
.PHONY : lib/mqtt_connect.cpp.o

lib/mqtt_connect.i: lib/mqtt_connect.cpp.i

.PHONY : lib/mqtt_connect.i

# target to preprocess a source file
lib/mqtt_connect.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_connect.cpp.i
.PHONY : lib/mqtt_connect.cpp.i

lib/mqtt_connect.s: lib/mqtt_connect.cpp.s

.PHONY : lib/mqtt_connect.s

# target to generate assembly for a file
lib/mqtt_connect.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_connect.cpp.s
.PHONY : lib/mqtt_connect.cpp.s

lib/mqtt_message.o: lib/mqtt_message.cpp.o

.PHONY : lib/mqtt_message.o

# target to build an object file
lib/mqtt_message.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message.cpp.o
.PHONY : lib/mqtt_message.cpp.o

lib/mqtt_message.i: lib/mqtt_message.cpp.i

.PHONY : lib/mqtt_message.i

# target to preprocess a source file
lib/mqtt_message.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message.cpp.i
.PHONY : lib/mqtt_message.cpp.i

lib/mqtt_message.s: lib/mqtt_message.cpp.s

.PHONY : lib/mqtt_message.s

# target to generate assembly for a file
lib/mqtt_message.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message.cpp.s
.PHONY : lib/mqtt_message.cpp.s

lib/mqtt_message_processor.o: lib/mqtt_message_processor.cpp.o

.PHONY : lib/mqtt_message_processor.o

# target to build an object file
lib/mqtt_message_processor.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message_processor.cpp.o
.PHONY : lib/mqtt_message_processor.cpp.o

lib/mqtt_message_processor.i: lib/mqtt_message_processor.cpp.i

.PHONY : lib/mqtt_message_processor.i

# target to preprocess a source file
lib/mqtt_message_processor.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message_processor.cpp.i
.PHONY : lib/mqtt_message_processor.cpp.i

lib/mqtt_message_processor.s: lib/mqtt_message_processor.cpp.s

.PHONY : lib/mqtt_message_processor.s

# target to generate assembly for a file
lib/mqtt_message_processor.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_message_processor.cpp.s
.PHONY : lib/mqtt_message_processor.cpp.s

lib/mqtt_package.o: lib/mqtt_package.cpp.o

.PHONY : lib/mqtt_package.o

# target to build an object file
lib/mqtt_package.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_package.cpp.o
.PHONY : lib/mqtt_package.cpp.o

lib/mqtt_package.i: lib/mqtt_package.cpp.i

.PHONY : lib/mqtt_package.i

# target to preprocess a source file
lib/mqtt_package.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_package.cpp.i
.PHONY : lib/mqtt_package.cpp.i

lib/mqtt_package.s: lib/mqtt_package.cpp.s

.PHONY : lib/mqtt_package.s

# target to generate assembly for a file
lib/mqtt_package.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_package.cpp.s
.PHONY : lib/mqtt_package.cpp.s

lib/mqtt_publish.o: lib/mqtt_publish.cpp.o

.PHONY : lib/mqtt_publish.o

# target to build an object file
lib/mqtt_publish.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_publish.cpp.o
.PHONY : lib/mqtt_publish.cpp.o

lib/mqtt_publish.i: lib/mqtt_publish.cpp.i

.PHONY : lib/mqtt_publish.i

# target to preprocess a source file
lib/mqtt_publish.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_publish.cpp.i
.PHONY : lib/mqtt_publish.cpp.i

lib/mqtt_publish.s: lib/mqtt_publish.cpp.s

.PHONY : lib/mqtt_publish.s

# target to generate assembly for a file
lib/mqtt_publish.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_publish.cpp.s
.PHONY : lib/mqtt_publish.cpp.s

lib/mqtt_subscribe.o: lib/mqtt_subscribe.cpp.o

.PHONY : lib/mqtt_subscribe.o

# target to build an object file
lib/mqtt_subscribe.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_subscribe.cpp.o
.PHONY : lib/mqtt_subscribe.cpp.o

lib/mqtt_subscribe.i: lib/mqtt_subscribe.cpp.i

.PHONY : lib/mqtt_subscribe.i

# target to preprocess a source file
lib/mqtt_subscribe.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_subscribe.cpp.i
.PHONY : lib/mqtt_subscribe.cpp.i

lib/mqtt_subscribe.s: lib/mqtt_subscribe.cpp.s

.PHONY : lib/mqtt_subscribe.s

# target to generate assembly for a file
lib/mqtt_subscribe.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_subscribe.cpp.s
.PHONY : lib/mqtt_subscribe.cpp.s

lib/mqtt_types.o: lib/mqtt_types.cpp.o

.PHONY : lib/mqtt_types.o

# target to build an object file
lib/mqtt_types.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_types.cpp.o
.PHONY : lib/mqtt_types.cpp.o

lib/mqtt_types.i: lib/mqtt_types.cpp.i

.PHONY : lib/mqtt_types.i

# target to preprocess a source file
lib/mqtt_types.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_types.cpp.i
.PHONY : lib/mqtt_types.cpp.i

lib/mqtt_types.s: lib/mqtt_types.cpp.s

.PHONY : lib/mqtt_types.s

# target to generate assembly for a file
lib/mqtt_types.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/mqtt_types.cpp.s
.PHONY : lib/mqtt_types.cpp.s

lib/qos_handler_factory.o: lib/qos_handler_factory.cpp.o

.PHONY : lib/qos_handler_factory.o

# target to build an object file
lib/qos_handler_factory.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_handler_factory.cpp.o
.PHONY : lib/qos_handler_factory.cpp.o

lib/qos_handler_factory.i: lib/qos_handler_factory.cpp.i

.PHONY : lib/qos_handler_factory.i

# target to preprocess a source file
lib/qos_handler_factory.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_handler_factory.cpp.i
.PHONY : lib/qos_handler_factory.cpp.i

lib/qos_handler_factory.s: lib/qos_handler_factory.cpp.s

.PHONY : lib/qos_handler_factory.s

# target to generate assembly for a file
lib/qos_handler_factory.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_handler_factory.cpp.s
.PHONY : lib/qos_handler_factory.cpp.s

lib/qos_one_handler.o: lib/qos_one_handler.cpp.o

.PHONY : lib/qos_one_handler.o

# target to build an object file
lib/qos_one_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_one_handler.cpp.o
.PHONY : lib/qos_one_handler.cpp.o

lib/qos_one_handler.i: lib/qos_one_handler.cpp.i

.PHONY : lib/qos_one_handler.i

# target to preprocess a source file
lib/qos_one_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_one_handler.cpp.i
.PHONY : lib/qos_one_handler.cpp.i

lib/qos_one_handler.s: lib/qos_one_handler.cpp.s

.PHONY : lib/qos_one_handler.s

# target to generate assembly for a file
lib/qos_one_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_one_handler.cpp.s
.PHONY : lib/qos_one_handler.cpp.s

lib/qos_two_handler.o: lib/qos_two_handler.cpp.o

.PHONY : lib/qos_two_handler.o

# target to build an object file
lib/qos_two_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_two_handler.cpp.o
.PHONY : lib/qos_two_handler.cpp.o

lib/qos_two_handler.i: lib/qos_two_handler.cpp.i

.PHONY : lib/qos_two_handler.i

# target to preprocess a source file
lib/qos_two_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_two_handler.cpp.i
.PHONY : lib/qos_two_handler.cpp.i

lib/qos_two_handler.s: lib/qos_two_handler.cpp.s

.PHONY : lib/qos_two_handler.s

# target to generate assembly for a file
lib/qos_two_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_two_handler.cpp.s
.PHONY : lib/qos_two_handler.cpp.s

lib/qos_zero_handler.o: lib/qos_zero_handler.cpp.o

.PHONY : lib/qos_zero_handler.o

# target to build an object file
lib/qos_zero_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_zero_handler.cpp.o
.PHONY : lib/qos_zero_handler.cpp.o

lib/qos_zero_handler.i: lib/qos_zero_handler.cpp.i

.PHONY : lib/qos_zero_handler.i

# target to preprocess a source file
lib/qos_zero_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_zero_handler.cpp.i
.PHONY : lib/qos_zero_handler.cpp.i

lib/qos_zero_handler.s: lib/qos_zero_handler.cpp.s

.PHONY : lib/qos_zero_handler.s

# target to generate assembly for a file
lib/qos_zero_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/qos_zero_handler.cpp.s
.PHONY : lib/qos_zero_handler.cpp.s

lib/subscriber.o: lib/subscriber.cpp.o

.PHONY : lib/subscriber.o

# target to build an object file
lib/subscriber.cpp.o:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/subscriber.cpp.o
.PHONY : lib/subscriber.cpp.o

lib/subscriber.i: lib/subscriber.cpp.i

.PHONY : lib/subscriber.i

# target to preprocess a source file
lib/subscriber.cpp.i:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/subscriber.cpp.i
.PHONY : lib/subscriber.cpp.i

lib/subscriber.s: lib/subscriber.cpp.s

.PHONY : lib/subscriber.s

# target to generate assembly for a file
lib/subscriber.cpp.s:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/lib/subscriber.cpp.s
.PHONY : lib/subscriber.cpp.s

src/client_handler.o: src/client_handler.cpp.o

.PHONY : src/client_handler.o

# target to build an object file
src/client_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/client_handler.cpp.o
.PHONY : src/client_handler.cpp.o

src/client_handler.i: src/client_handler.cpp.i

.PHONY : src/client_handler.i

# target to preprocess a source file
src/client_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/client_handler.cpp.i
.PHONY : src/client_handler.cpp.i

src/client_handler.s: src/client_handler.cpp.s

.PHONY : src/client_handler.s

# target to generate assembly for a file
src/client_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/client_handler.cpp.s
.PHONY : src/client_handler.cpp.s

src/http_rest_server.o: src/http_rest_server.cpp.o

.PHONY : src/http_rest_server.o

# target to build an object file
src/http_rest_server.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/http_rest_server.cpp.o
.PHONY : src/http_rest_server.cpp.o

src/http_rest_server.i: src/http_rest_server.cpp.i

.PHONY : src/http_rest_server.i

# target to preprocess a source file
src/http_rest_server.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/http_rest_server.cpp.i
.PHONY : src/http_rest_server.cpp.i

src/http_rest_server.s: src/http_rest_server.cpp.s

.PHONY : src/http_rest_server.s

# target to generate assembly for a file
src/http_rest_server.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/http_rest_server.cpp.s
.PHONY : src/http_rest_server.cpp.s

src/in_memory_storage.o: src/in_memory_storage.cpp.o

.PHONY : src/in_memory_storage.o

# target to build an object file
src/in_memory_storage.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/in_memory_storage.cpp.o
.PHONY : src/in_memory_storage.cpp.o

src/in_memory_storage.i: src/in_memory_storage.cpp.i

.PHONY : src/in_memory_storage.i

# target to preprocess a source file
src/in_memory_storage.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/in_memory_storage.cpp.i
.PHONY : src/in_memory_storage.cpp.i

src/in_memory_storage.s: src/in_memory_storage.cpp.s

.PHONY : src/in_memory_storage.s

# target to generate assembly for a file
src/in_memory_storage.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/in_memory_storage.cpp.s
.PHONY : src/in_memory_storage.cpp.s

src/login_allow_anonymous_handler.o: src/login_allow_anonymous_handler.cpp.o

.PHONY : src/login_allow_anonymous_handler.o

# target to build an object file
src/login_allow_anonymous_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_allow_anonymous_handler.cpp.o
.PHONY : src/login_allow_anonymous_handler.cpp.o

src/login_allow_anonymous_handler.i: src/login_allow_anonymous_handler.cpp.i

.PHONY : src/login_allow_anonymous_handler.i

# target to preprocess a source file
src/login_allow_anonymous_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_allow_anonymous_handler.cpp.i
.PHONY : src/login_allow_anonymous_handler.cpp.i

src/login_allow_anonymous_handler.s: src/login_allow_anonymous_handler.cpp.s

.PHONY : src/login_allow_anonymous_handler.s

# target to generate assembly for a file
src/login_allow_anonymous_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_allow_anonymous_handler.cpp.s
.PHONY : src/login_allow_anonymous_handler.cpp.s

src/login_factory.o: src/login_factory.cpp.o

.PHONY : src/login_factory.o

# target to build an object file
src/login_factory.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_factory.cpp.o
.PHONY : src/login_factory.cpp.o

src/login_factory.i: src/login_factory.cpp.i

.PHONY : src/login_factory.i

# target to preprocess a source file
src/login_factory.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_factory.cpp.i
.PHONY : src/login_factory.cpp.i

src/login_factory.s: src/login_factory.cpp.s

.PHONY : src/login_factory.s

# target to generate assembly for a file
src/login_factory.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_factory.cpp.s
.PHONY : src/login_factory.cpp.s

src/login_handler.o: src/login_handler.cpp.o

.PHONY : src/login_handler.o

# target to build an object file
src/login_handler.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_handler.cpp.o
.PHONY : src/login_handler.cpp.o

src/login_handler.i: src/login_handler.cpp.i

.PHONY : src/login_handler.i

# target to preprocess a source file
src/login_handler.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_handler.cpp.i
.PHONY : src/login_handler.cpp.i

src/login_handler.s: src/login_handler.cpp.s

.PHONY : src/login_handler.s

# target to generate assembly for a file
src/login_handler.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/login_handler.cpp.s
.PHONY : src/login_handler.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/server.o: src/server.cpp.o

.PHONY : src/server.o

# target to build an object file
src/server.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/server.cpp.o
.PHONY : src/server.cpp.o

src/server.i: src/server.cpp.i

.PHONY : src/server.i

# target to preprocess a source file
src/server.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/server.cpp.i
.PHONY : src/server.cpp.i

src/server.s: src/server.cpp.s

.PHONY : src/server.s

# target to generate assembly for a file
src/server.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/server.cpp.s
.PHONY : src/server.cpp.s

src/ssl_client_factory.o: src/ssl_client_factory.cpp.o

.PHONY : src/ssl_client_factory.o

# target to build an object file
src/ssl_client_factory.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/ssl_client_factory.cpp.o
.PHONY : src/ssl_client_factory.cpp.o

src/ssl_client_factory.i: src/ssl_client_factory.cpp.i

.PHONY : src/ssl_client_factory.i

# target to preprocess a source file
src/ssl_client_factory.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/ssl_client_factory.cpp.i
.PHONY : src/ssl_client_factory.cpp.i

src/ssl_client_factory.s: src/ssl_client_factory.cpp.s

.PHONY : src/ssl_client_factory.s

# target to generate assembly for a file
src/ssl_client_factory.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/ssl_client_factory.cpp.s
.PHONY : src/ssl_client_factory.cpp.s

src/startup_configuration.o: src/startup_configuration.cpp.o

.PHONY : src/startup_configuration.o

# target to build an object file
src/startup_configuration.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/startup_configuration.cpp.o
.PHONY : src/startup_configuration.cpp.o

src/startup_configuration.i: src/startup_configuration.cpp.i

.PHONY : src/startup_configuration.i

# target to preprocess a source file
src/startup_configuration.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/startup_configuration.cpp.i
.PHONY : src/startup_configuration.cpp.i

src/startup_configuration.s: src/startup_configuration.cpp.s

.PHONY : src/startup_configuration.s

# target to generate assembly for a file
src/startup_configuration.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/startup_configuration.cpp.s
.PHONY : src/startup_configuration.cpp.s

src/string.o: src/string.cpp.o

.PHONY : src/string.o

# target to build an object file
src/string.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/string.cpp.o
.PHONY : src/string.cpp.o

src/string.i: src/string.cpp.i

.PHONY : src/string.i

# target to preprocess a source file
src/string.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/string.cpp.i
.PHONY : src/string.cpp.i

src/string.s: src/string.cpp.s

.PHONY : src/string.s

# target to generate assembly for a file
src/string.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/string.cpp.s
.PHONY : src/string.cpp.s

src/subscriber_container.o: src/subscriber_container.cpp.o

.PHONY : src/subscriber_container.o

# target to build an object file
src/subscriber_container.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_container.cpp.o
.PHONY : src/subscriber_container.cpp.o

src/subscriber_container.i: src/subscriber_container.cpp.i

.PHONY : src/subscriber_container.i

# target to preprocess a source file
src/subscriber_container.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_container.cpp.i
.PHONY : src/subscriber_container.cpp.i

src/subscriber_container.s: src/subscriber_container.cpp.s

.PHONY : src/subscriber_container.s

# target to generate assembly for a file
src/subscriber_container.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_container.cpp.s
.PHONY : src/subscriber_container.cpp.s

src/subscriber_node.o: src/subscriber_node.cpp.o

.PHONY : src/subscriber_node.o

# target to build an object file
src/subscriber_node.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_node.cpp.o
.PHONY : src/subscriber_node.cpp.o

src/subscriber_node.i: src/subscriber_node.cpp.i

.PHONY : src/subscriber_node.i

# target to preprocess a source file
src/subscriber_node.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_node.cpp.i
.PHONY : src/subscriber_node.cpp.i

src/subscriber_node.s: src/subscriber_node.cpp.s

.PHONY : src/subscriber_node.s

# target to generate assembly for a file
src/subscriber_node.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/subscriber_node.cpp.s
.PHONY : src/subscriber_node.cpp.s

src/tcp_client_factory.o: src/tcp_client_factory.cpp.o

.PHONY : src/tcp_client_factory.o

# target to build an object file
src/tcp_client_factory.cpp.o:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/tcp_client_factory.cpp.o
.PHONY : src/tcp_client_factory.cpp.o

src/tcp_client_factory.i: src/tcp_client_factory.cpp.i

.PHONY : src/tcp_client_factory.i

# target to preprocess a source file
src/tcp_client_factory.cpp.i:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/tcp_client_factory.cpp.i
.PHONY : src/tcp_client_factory.cpp.i

src/tcp_client_factory.s: src/tcp_client_factory.cpp.s

.PHONY : src/tcp_client_factory.s

# target to generate assembly for a file
src/tcp_client_factory.cpp.s:
	$(MAKE) -f CMakeFiles/pmq_obj_lib.dir/build.make CMakeFiles/pmq_obj_lib.dir/src/tcp_client_factory.cpp.s
.PHONY : src/tcp_client_factory.cpp.s

test/test_login_factory.o: test/test_login_factory.cpp.o

.PHONY : test/test_login_factory.o

# target to build an object file
test/test_login_factory.cpp.o:
	$(MAKE) -f CMakeFiles/test_login_factory.dir/build.make CMakeFiles/test_login_factory.dir/test/test_login_factory.cpp.o
.PHONY : test/test_login_factory.cpp.o

test/test_login_factory.i: test/test_login_factory.cpp.i

.PHONY : test/test_login_factory.i

# target to preprocess a source file
test/test_login_factory.cpp.i:
	$(MAKE) -f CMakeFiles/test_login_factory.dir/build.make CMakeFiles/test_login_factory.dir/test/test_login_factory.cpp.i
.PHONY : test/test_login_factory.cpp.i

test/test_login_factory.s: test/test_login_factory.cpp.s

.PHONY : test/test_login_factory.s

# target to generate assembly for a file
test/test_login_factory.cpp.s:
	$(MAKE) -f CMakeFiles/test_login_factory.dir/build.make CMakeFiles/test_login_factory.dir/test/test_login_factory.cpp.s
.PHONY : test/test_login_factory.cpp.s

test/test_login_handler.o: test/test_login_handler.cpp.o

.PHONY : test/test_login_handler.o

# target to build an object file
test/test_login_handler.cpp.o:
	$(MAKE) -f CMakeFiles/test_login_handler.dir/build.make CMakeFiles/test_login_handler.dir/test/test_login_handler.cpp.o
.PHONY : test/test_login_handler.cpp.o

test/test_login_handler.i: test/test_login_handler.cpp.i

.PHONY : test/test_login_handler.i

# target to preprocess a source file
test/test_login_handler.cpp.i:
	$(MAKE) -f CMakeFiles/test_login_handler.dir/build.make CMakeFiles/test_login_handler.dir/test/test_login_handler.cpp.i
.PHONY : test/test_login_handler.cpp.i

test/test_login_handler.s: test/test_login_handler.cpp.s

.PHONY : test/test_login_handler.s

# target to generate assembly for a file
test/test_login_handler.cpp.s:
	$(MAKE) -f CMakeFiles/test_login_handler.dir/build.make CMakeFiles/test_login_handler.dir/test/test_login_handler.cpp.s
.PHONY : test/test_login_handler.cpp.s

test/test_server.o: test/test_server.cpp.o

.PHONY : test/test_server.o

# target to build an object file
test/test_server.cpp.o:
	$(MAKE) -f CMakeFiles/test_server.dir/build.make CMakeFiles/test_server.dir/test/test_server.cpp.o
.PHONY : test/test_server.cpp.o

test/test_server.i: test/test_server.cpp.i

.PHONY : test/test_server.i

# target to preprocess a source file
test/test_server.cpp.i:
	$(MAKE) -f CMakeFiles/test_server.dir/build.make CMakeFiles/test_server.dir/test/test_server.cpp.i
.PHONY : test/test_server.cpp.i

test/test_server.s: test/test_server.cpp.s

.PHONY : test/test_server.s

# target to generate assembly for a file
test/test_server.cpp.s:
	$(MAKE) -f CMakeFiles/test_server.dir/build.make CMakeFiles/test_server.dir/test/test_server.cpp.s
.PHONY : test/test_server.cpp.s

test/test_subscriber_container.o: test/test_subscriber_container.cpp.o

.PHONY : test/test_subscriber_container.o

# target to build an object file
test/test_subscriber_container.cpp.o:
	$(MAKE) -f CMakeFiles/test_subscriber_container.dir/build.make CMakeFiles/test_subscriber_container.dir/test/test_subscriber_container.cpp.o
.PHONY : test/test_subscriber_container.cpp.o

test/test_subscriber_container.i: test/test_subscriber_container.cpp.i

.PHONY : test/test_subscriber_container.i

# target to preprocess a source file
test/test_subscriber_container.cpp.i:
	$(MAKE) -f CMakeFiles/test_subscriber_container.dir/build.make CMakeFiles/test_subscriber_container.dir/test/test_subscriber_container.cpp.i
.PHONY : test/test_subscriber_container.cpp.i

test/test_subscriber_container.s: test/test_subscriber_container.cpp.s

.PHONY : test/test_subscriber_container.s

# target to generate assembly for a file
test/test_subscriber_container.cpp.s:
	$(MAKE) -f CMakeFiles/test_subscriber_container.dir/build.make CMakeFiles/test_subscriber_container.dir/test/test_subscriber_container.cpp.s
.PHONY : test/test_subscriber_container.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... test_subscriber_container"
	@echo "... test_login_factory"
	@echo "... PMQ"
	@echo "... pmq_obj_lib"
	@echo "... rebuild_cache"
	@echo "... test_server"
	@echo "... pmqtt"
	@echo "... test_login_handler"
	@echo "... pmqttclient"
	@echo "... client/messenger.o"
	@echo "... client/messenger.i"
	@echo "... client/messenger.s"
	@echo "... lib/message.o"
	@echo "... lib/message.i"
	@echo "... lib/message.s"
	@echo "... lib/mqtt_connect.o"
	@echo "... lib/mqtt_connect.i"
	@echo "... lib/mqtt_connect.s"
	@echo "... lib/mqtt_message.o"
	@echo "... lib/mqtt_message.i"
	@echo "... lib/mqtt_message.s"
	@echo "... lib/mqtt_message_processor.o"
	@echo "... lib/mqtt_message_processor.i"
	@echo "... lib/mqtt_message_processor.s"
	@echo "... lib/mqtt_package.o"
	@echo "... lib/mqtt_package.i"
	@echo "... lib/mqtt_package.s"
	@echo "... lib/mqtt_publish.o"
	@echo "... lib/mqtt_publish.i"
	@echo "... lib/mqtt_publish.s"
	@echo "... lib/mqtt_subscribe.o"
	@echo "... lib/mqtt_subscribe.i"
	@echo "... lib/mqtt_subscribe.s"
	@echo "... lib/mqtt_types.o"
	@echo "... lib/mqtt_types.i"
	@echo "... lib/mqtt_types.s"
	@echo "... lib/qos_handler_factory.o"
	@echo "... lib/qos_handler_factory.i"
	@echo "... lib/qos_handler_factory.s"
	@echo "... lib/qos_one_handler.o"
	@echo "... lib/qos_one_handler.i"
	@echo "... lib/qos_one_handler.s"
	@echo "... lib/qos_two_handler.o"
	@echo "... lib/qos_two_handler.i"
	@echo "... lib/qos_two_handler.s"
	@echo "... lib/qos_zero_handler.o"
	@echo "... lib/qos_zero_handler.i"
	@echo "... lib/qos_zero_handler.s"
	@echo "... lib/subscriber.o"
	@echo "... lib/subscriber.i"
	@echo "... lib/subscriber.s"
	@echo "... src/client_handler.o"
	@echo "... src/client_handler.i"
	@echo "... src/client_handler.s"
	@echo "... src/http_rest_server.o"
	@echo "... src/http_rest_server.i"
	@echo "... src/http_rest_server.s"
	@echo "... src/in_memory_storage.o"
	@echo "... src/in_memory_storage.i"
	@echo "... src/in_memory_storage.s"
	@echo "... src/login_allow_anonymous_handler.o"
	@echo "... src/login_allow_anonymous_handler.i"
	@echo "... src/login_allow_anonymous_handler.s"
	@echo "... src/login_factory.o"
	@echo "... src/login_factory.i"
	@echo "... src/login_factory.s"
	@echo "... src/login_handler.o"
	@echo "... src/login_handler.i"
	@echo "... src/login_handler.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/server.o"
	@echo "... src/server.i"
	@echo "... src/server.s"
	@echo "... src/ssl_client_factory.o"
	@echo "... src/ssl_client_factory.i"
	@echo "... src/ssl_client_factory.s"
	@echo "... src/startup_configuration.o"
	@echo "... src/startup_configuration.i"
	@echo "... src/startup_configuration.s"
	@echo "... src/string.o"
	@echo "... src/string.i"
	@echo "... src/string.s"
	@echo "... src/subscriber_container.o"
	@echo "... src/subscriber_container.i"
	@echo "... src/subscriber_container.s"
	@echo "... src/subscriber_node.o"
	@echo "... src/subscriber_node.i"
	@echo "... src/subscriber_node.s"
	@echo "... src/tcp_client_factory.o"
	@echo "... src/tcp_client_factory.i"
	@echo "... src/tcp_client_factory.s"
	@echo "... test/test_login_factory.o"
	@echo "... test/test_login_factory.i"
	@echo "... test/test_login_factory.s"
	@echo "... test/test_login_handler.o"
	@echo "... test/test_login_handler.i"
	@echo "... test/test_login_handler.s"
	@echo "... test/test_server.o"
	@echo "... test/test_server.i"
	@echo "... test/test_server.s"
	@echo "... test/test_subscriber_container.o"
	@echo "... test/test_subscriber_container.i"
	@echo "... test/test_subscriber_container.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

