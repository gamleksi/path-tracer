cmake_minimum_required(VERSION 3.12)
project(path_tracer)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_subdirectory(tests)
add_executable(path_tracer src/main.cpp include)
