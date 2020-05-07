add_library(doctest INTERFACE)
target_include_directories(doctest
  SYSTEM INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/doctest>
)
add_library(doctest::doctest ALIAS doctest)

add_library(doctest_main STATIC)
target_sources(doctest_main PRIVATE doctest_main.cpp)
target_link_libraries(doctest_main PUBLIC doctest)
add_library(doctest::doctest_main ALIAS doctest_main)

add_library(rangev3 INTERFACE)
target_include_directories(rangev3
  SYSTEM INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/range-v3/include>
)

add_library(rangev3::range ALIAS rangev3)

add_subdirectory(fmt)
