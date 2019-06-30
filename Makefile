# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cefour/Projects/pmq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cefour/Projects/pmq

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/CLion.app/Contents/bin/cmake/mac/bin/cmake" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"/Users/cefour/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

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
# Target rules for targets named pmqtt

# Build rule for target.
pmqtt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pmqtt
.PHONY : pmqtt

# fast build rule for target.
pmqtt/fast:
	$(MAKE) -f CMakeFiles/pmqtt.dir/build.make CMakeFiles/pmqtt.dir/build
.PHONY : pmqtt/fast

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
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/client_handler.cpp.o
.PHONY : src/client_handler.cpp.o

src/client_handler.i: src/client_handler.cpp.i

.PHONY : src/client_handler.i

# target to preprocess a source file
src/client_handler.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/client_handler.cpp.i
.PHONY : src/client_handler.cpp.i

src/client_handler.s: src/client_handler.cpp.s

.PHONY : src/client_handler.s

# target to generate assembly for a file
src/client_handler.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/client_handler.cpp.s
.PHONY : src/client_handler.cpp.s

src/http_rest_server.o: src/http_rest_server.cpp.o

.PHONY : src/http_rest_server.o

# target to build an object file
src/http_rest_server.cpp.o:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/http_rest_server.cpp.o
.PHONY : src/http_rest_server.cpp.o

src/http_rest_server.i: src/http_rest_server.cpp.i

.PHONY : src/http_rest_server.i

# target to preprocess a source file
src/http_rest_server.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/http_rest_server.cpp.i
.PHONY : src/http_rest_server.cpp.i

src/http_rest_server.s: src/http_rest_server.cpp.s

.PHONY : src/http_rest_server.s

# target to generate assembly for a file
src/http_rest_server.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/http_rest_server.cpp.s
.PHONY : src/http_rest_server.cpp.s

src/in_memory_storage.o: src/in_memory_storage.cpp.o

.PHONY : src/in_memory_storage.o

# target to build an object file
src/in_memory_storage.cpp.o:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/in_memory_storage.cpp.o
.PHONY : src/in_memory_storage.cpp.o

src/in_memory_storage.i: src/in_memory_storage.cpp.i

.PHONY : src/in_memory_storage.i

# target to preprocess a source file
src/in_memory_storage.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/in_memory_storage.cpp.i
.PHONY : src/in_memory_storage.cpp.i

src/in_memory_storage.s: src/in_memory_storage.cpp.s

.PHONY : src/in_memory_storage.s

# target to generate assembly for a file
src/in_memory_storage.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/in_memory_storage.cpp.s
.PHONY : src/in_memory_storage.cpp.s

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
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/server.cpp.o
.PHONY : src/server.cpp.o

src/server.i: src/server.cpp.i

.PHONY : src/server.i

# target to preprocess a source file
src/server.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/server.cpp.i
.PHONY : src/server.cpp.i

src/server.s: src/server.cpp.s

.PHONY : src/server.s

# target to generate assembly for a file
src/server.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/server.cpp.s
.PHONY : src/server.cpp.s

src/ssl_client_factory.o: src/ssl_client_factory.cpp.o

.PHONY : src/ssl_client_factory.o

# target to build an object file
src/ssl_client_factory.cpp.o:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/ssl_client_factory.cpp.o
.PHONY : src/ssl_client_factory.cpp.o

src/ssl_client_factory.i: src/ssl_client_factory.cpp.i

.PHONY : src/ssl_client_factory.i

# target to preprocess a source file
src/ssl_client_factory.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/ssl_client_factory.cpp.i
.PHONY : src/ssl_client_factory.cpp.i

src/ssl_client_factory.s: src/ssl_client_factory.cpp.s

.PHONY : src/ssl_client_factory.s

# target to generate assembly for a file
src/ssl_client_factory.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/ssl_client_factory.cpp.s
.PHONY : src/ssl_client_factory.cpp.s

src/tcp_client_factory.o: src/tcp_client_factory.cpp.o

.PHONY : src/tcp_client_factory.o

# target to build an object file
src/tcp_client_factory.cpp.o:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/tcp_client_factory.cpp.o
.PHONY : src/tcp_client_factory.cpp.o

src/tcp_client_factory.i: src/tcp_client_factory.cpp.i

.PHONY : src/tcp_client_factory.i

# target to preprocess a source file
src/tcp_client_factory.cpp.i:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/tcp_client_factory.cpp.i
.PHONY : src/tcp_client_factory.cpp.i

src/tcp_client_factory.s: src/tcp_client_factory.cpp.s

.PHONY : src/tcp_client_factory.s

# target to generate assembly for a file
src/tcp_client_factory.cpp.s:
	$(MAKE) -f CMakeFiles/PMQ.dir/build.make CMakeFiles/PMQ.dir/src/tcp_client_factory.cpp.s
.PHONY : src/tcp_client_factory.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... PMQ"
	@echo "... pmqtt"
	@echo "... lib/mqtt_connect.o"
	@echo "... lib/mqtt_connect.i"
	@echo "... lib/mqtt_connect.s"
	@echo "... lib/mqtt_message.o"
	@echo "... lib/mqtt_message.i"
	@echo "... lib/mqtt_message.s"
	@echo "... lib/mqtt_package.o"
	@echo "... lib/mqtt_package.i"
	@echo "... lib/mqtt_package.s"
	@echo "... lib/mqtt_publish.o"
	@echo "... lib/mqtt_publish.i"
	@echo "... lib/mqtt_publish.s"
	@echo "... lib/mqtt_subscribe.o"
	@echo "... lib/mqtt_subscribe.i"
	@echo "... lib/mqtt_subscribe.s"
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
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/server.o"
	@echo "... src/server.i"
	@echo "... src/server.s"
	@echo "... src/ssl_client_factory.o"
	@echo "... src/ssl_client_factory.i"
	@echo "... src/ssl_client_factory.s"
	@echo "... src/tcp_client_factory.o"
	@echo "... src/tcp_client_factory.i"
	@echo "... src/tcp_client_factory.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

