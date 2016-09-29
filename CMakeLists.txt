cmake_minimum_required(VERSION 2.8)
project(dash)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g")

add_subdirectory(src)