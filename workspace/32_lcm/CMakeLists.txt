cmake_minimum_required(VERSION 2.8.12)

# The project needs to be defined after the toolchain setup.
project(lcm)

set(CMAKE_SYSTEM_NAME Linux)
#set(TOOLCHAIN_PREFIX aarch64-linux-gnu)

# cross compilers to use for C and C++
set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# target environment on the build host system
#   set 1st to dir with the cross compiler's C/C++ headers/libs
#set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

# modify default behavior of FIND_XXX() commands to
# search for headers/libs in the target environment and
# search for programs in the build host environment
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# We want a lots of warnings.
set (CMAKE_C_FLAGS "-Wall -g --std=gnu11${CMAKE_C_FLAGS}")
#set (CMAKE_CXX_FLAGS "-O3 -Wfatal-errors -Wall -Wextra -Werror  ${CMAKE_CXX_FLAGS}")
#set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")

include_directories(
	include/
)

#link_directories (${CMAKE_SOURCE_DIR}/liblcm)

add_executable(buftest-receiver
	buftest-receiver.c
)

add_executable(buftest-sender
	buftest-sender.c
)

target_link_libraries(buftest-receiver
	${CMAKE_SOURCE_DIR}/liblcm/liblcm.so
	gcc
	gcc_s
	m
)

target_link_libraries(buftest-sender
	${CMAKE_SOURCE_DIR}/liblcm/liblcm.so	
	gcc
	gcc_s
	m
)