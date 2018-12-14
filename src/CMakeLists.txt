cmake_minimum_required(VERSION 3.5.1)
project(path_tracer)


find_package( Boost COMPONENTS program_options REQUIRED )
include_directories(${Boost_INCLUDE_DIR} )

if(${APPLE})
message("You are using an Apple product.")
set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I /usr/local/opt/libomp/include")
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I /usr/local/opt/libomp/include")
set(OpenMP_CXX_LIB_LIBRARY "/usr/local/opt/libomp/lib")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY /usr/local/opt/libomp/lib/libomp.dylib)
find_package(OpenMP REQUIRED)
include_directories("${OpenMP_CXX_LIB_LIBRARY}")
else(${APPLE})
message("You are using Ubuntu.")
message("This CMake does not take into account Windows :) .")
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SFML COMPONENTS Graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

# add_subdirectory(tests)
add_executable(path_tracer src/main.cpp include include/intersection/bounding_box.cpp
        include/geometry/geometry.cpp include/camera/camera.cpp
        include/material/material.cpp include/geometry/sphere.cpp include/geometry/sphere.h
        include/geometry/box.cpp include/geometry/box.h include/geometry/bv_node.cpp include/geometry/bv_node.h
        include/geometry/geomlist.cpp include/geometry/geomlist.h)

if(${APPLE})
target_link_libraries(path_tracer OpenMP::OpenMP_CXX ${SFML_LIBRARIES} ${Boost_LIBRARIES})
else(${APPLE})
target_link_libraries(path_tracer ${SFML_LIBRARIES} ${Boost_LIBRARIES})
endif()

