cmake_minimum_required(VERSION 3.12)
project(path_tracer)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I /usr/local/opt/libomp/include")
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I /usr/local/opt/libomp/include")
set(OpenMP_CXX_LIB_LIBRARY "/usr/local/opt/libomp/lib")

set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY /usr/local/opt/libomp/lib/libomp.dylib)

find_package(OpenMP REQUIRED)
include_directories("${OpenMP_CXX_LIB_LIBRARY}")

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_subdirectory(tests)
add_executable(path_tracer src/main.cpp include include/intersection/bounding_box.cpp
        include/geometry/geometry.cpp include/camera/camera.cpp
        include/material/material.cpp)

target_link_libraries(path_tracer ${OpenCV_LIBS} OpenMP::OpenMP_CXX)

# include/io/io.cpp
# https://iscinumpy.gitlab.io/post/omp-on-high-sierra/
# https://stackoverflow.com/questions/46414660/macos-cmake-and-openmp
# https://stackoverflow.com/questions/12399422/how-to-set-linker-flags-for-openmp-in-cmakes-try-compile-function/12404666#12404666
