cmake_minimum_required(VERSION 3.14)
project(zotti_asd_project)

set(CMAKE_CXX_STANDARD 14)

if (GET_TIMINGS)
    add_definitions(-DGET_TIMINGS)
endif ()

set(SOURCES main.cpp include/main.h include/timings.h src/timings.cpp include/input_handeler.h src/input_handeler.cpp)

add_executable(zotti_asd_project ${SOURCES})
target_include_directories(zotti_asd_project PRIVATE include)

add_executable(zotti_asd_project_timings ${SOURCES})
target_include_directories(zotti_asd_project_timings PRIVATE include)
target_compile_definitions(zotti_asd_project_timings PRIVATE -DGET_TIMINGS)