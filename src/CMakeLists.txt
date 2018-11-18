cmake_minimum_required(VERSION 3.12)
project(path_tracer)

find_package(OpenCV REQUIRED)

message(${OpenCV_LIBS})
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_subdirectory(tests)
add_executable(path_tracer src/main.cpp include include/geometry/geometry.cpp include/camera/camera.cpp include/hitable/hitable.h)
target_link_libraries(path_tracer ${OpenCV_LIBS})
