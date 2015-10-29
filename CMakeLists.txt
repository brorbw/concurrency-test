cmake_minimum_required(VERSION 3.3)
project(grafjo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp circular_array.cpp circular_array.h)
add_executable(grafjo ${SOURCE_FILES})