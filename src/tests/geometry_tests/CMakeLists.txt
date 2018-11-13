include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

include_directories(../../include)

add_executable(geometry_test geometry_check.cpp ../../include)
target_link_libraries(geometry_test gtest gtest_main)
