project(ray_tests)

include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

include_directories(../../include)

add_executable(ray_tests ray_check.cpp ../../include ../../src)
target_link_libraries(ray_tests gtest gtest_main)

