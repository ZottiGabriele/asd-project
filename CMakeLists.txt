cmake_minimum_required(VERSION 3.14)
project(asd_project)

set(CMAKE_CXX_STANDARD 14)

if (GET_TIMINGS)
    add_definitions(-DGET_TIMINGS)
endif ()

set(SOURCES main.cpp include/main.h include/timings.h src/timings.cpp include/input_handeler.h src/input_handeler.cpp)

add_executable(asd_project ${SOURCES})
target_include_directories(asd_project PRIVATE /Users/gabrielezotti/Documents/asd-project/include)