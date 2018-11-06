include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

include_directories(../../include)

add_executable(vector_test algebra_check.cpp ../../include)
target_link_libraries(vector_test gtest gtest_main)

