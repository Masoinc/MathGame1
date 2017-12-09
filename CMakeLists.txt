cmake_minimum_required(VERSION 3.5)
project(MathGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LinkNode.h Link.cpp)
add_executable(MathGame ${SOURCE_FILES} LinkNode.h Link.cpp)