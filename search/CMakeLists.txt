cmake_minimum_required(VERSION 3.4)
project(search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_CXX_COMPILER gcc)
set(SOURCE_FILES main.c compressed_prefix_tree/compressed_prefix_tree.h read_file/read_file.h tests/tests.h read_file/read_file.c compressed_prefix_tree/compressed_prefix_tree.c tests/tests.c)
add_executable(search ${SOURCE_FILES})