cmake_minimum_required(VERSION 3.14)
project(asd_project)

set(CMAKE_CXX_STANDARD 14)

if (GET_TIMINGS)
    add_definitions(-DGET_TIMINGS)
endif ()

add_executable(asd_project main.cpp)