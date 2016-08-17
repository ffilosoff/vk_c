cmake_minimum_required(VERSION 3.4)
project(test_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c bsearch.h)
add_executable(test_proj ${SOURCE_FILES})