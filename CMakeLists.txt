cmake_minimum_required(VERSION 2.8)
project(dash)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)