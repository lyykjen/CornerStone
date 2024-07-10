cmake_minimum_required(VERSION 2.8.12)

# The project needs to be defined after the toolchain setup.
project(test)
set(CMAKE_SYSTEM_NAME Linux)

# cross compilers to use for C and C++
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# modify default behavior of FIND_XXX() commands to
# search for headers/libs in the target environment and
# search for programs in the build host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# We want a lots of warnings.
add_definitions("-O3 -Wfatal-errors -Wall -Wextra -Werror -Wno-missing-field-initializers")

set (CMAKE_C_FLAGS "--std=gnu11 ${CMAKE_C_FLAGS}")
set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")


include_directories(
)

add_executable(test_queue
	queue.c
	Queue.h
	test_queue.c
)

target_link_libraries(test_queue
	c
	gcc
	gcc_s
	m
	pthread
)
