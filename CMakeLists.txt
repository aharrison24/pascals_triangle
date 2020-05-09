cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(pascals_triangle)

add_subdirectory(thirdparty)

add_executable(pascals_triangle_tests
  pascals_triangle.h
  pascals_triangle.cpp
  pascals_triangle_tests.cpp
)

target_link_libraries(pascals_triangle_tests
  PRIVATE
    doctest::doctest_main
    rangev3::range
    fmt::fmt
)

target_compile_definitions(pascals_triangle_tests
  PRIVATE
    SOLUTION_NAMESPACE=pascals_triangle
)
