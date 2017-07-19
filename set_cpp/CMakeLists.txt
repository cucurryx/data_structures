cmake_minimum_required(VERSION 3.3)
project(set_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rb_tree.h rb_tree.cpp set.h set.cpp)
add_executable(set_cpp ${SOURCE_FILES})