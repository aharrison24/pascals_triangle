cmake_minimum_required(VERSION 3.12)


project(pascals_triangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# ------------------------------------------------------------------------------
add_subdirectory(thirdparty)

# ------------------------------------------------------------------------------
set(COMMON_WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wunused # warn on anything being unused
  -Wcast-align # warn for potential performance problem casts
  -Wnull-dereference # warn if a null dereference is detected
  -Wformat=2 # warn on security issues around functions that format output
             # (ie printf)
  -Woverloaded-virtual # warn if you overload (not override) a virtual
                       # function
  -Wshadow # warn the user if a variable declaration shadows one from a
           # parent context
  -Wpedantic # warn if non-standard C++ is used
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                     # non-virtual destructor. This helps catch hard to
                     # track down memory errors
  -Wold-style-cast # warn for c-style casts
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")           # Matches AppleClang too
  set(WARNING_FLAGS ${COMMON_WARNINGS})
elseif(PARAM_COMPILER_NAME STREQUAL "GNU")
  set(WARNING_FLAGS
    ${COMMON_WARNINGS}
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wlogical-op # warn about logical operations being used where bitwise were
                 # probably wanted
    -Wuseless-cast # warn if you perform a cast to the same type
  )
else()
  set(WARNING_FLAGS)
endif()
add_compile_options(${WARNING_FLAGS})

# ------------------------------------------------------------------------------

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
