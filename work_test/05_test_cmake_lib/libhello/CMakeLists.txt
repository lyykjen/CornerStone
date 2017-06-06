cmake_minimum_required(VERSION 2.8)
set(LIB_SRC hello.c)
add_library(libhello STATIC ${LIB_SRC})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
install(TARGETS libhello
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
install(FILES hello.h DESTINATION include/hello)
