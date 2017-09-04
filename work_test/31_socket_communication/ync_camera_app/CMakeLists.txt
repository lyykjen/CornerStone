cmake_minimum_required(VERSION 2.8.12)

# The project needs to be defined after the toolchain setup.
project(ync_app)

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
	mavlink2/
)

add_executable(ync_app
	ync_app.c
)

target_link_libraries(ync_app
	gcc
	gcc_s
	m
	pthread
)
