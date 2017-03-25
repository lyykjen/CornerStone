cmake_minimum_required(VERSION 2.8.12)

project(lane)
set(CROSS_COMPILE arm-linux-gnueabihf-)
set(COMPILE_C_TOOL gcc)
set(COMPILE_CXX_TOOL g++)
set(CMAKE_C_COMPILER ${COMPILE_C_TOOL})
set(CMAKE_CXX_COMPILER ${COMPILE_CXX_TOOL})

# We want a lots of warnings.
set (CMAKE_C_FLAGS "-O3 -Wfatal-errors --std=gnu11 ${CMAKE_C_FLAGS}")
set (CMAKE_CXX_FLAGS " -Wall -Werror -O2 -fPIC -Wextra -Werror ${CMAKE_CXX_FLAGS}")
#set (CMAKE_CXX_FLAGS "-O3 -Wfatal-errors -Wall -Wextra -Werror ${CMAKE_CXX_FLAGS}")
set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")


add_executable(lane
	main.c
	line_filter.c
	LDWS.c
	Lane_width_transfer_distance.c
	hough_combine.c
	detect_curve.c
	check_lane_type.c
	car_serch.c
	car_back_light.c
	parallax.c
)


target_link_libraries(lane
	#${CMAKE_SOURCE_DIR}/libstdc++/libstdc++.so.6
	c
	gcc
	gcc_s
	m
	pthread
)
