# There is much nastiness here, because we need to compile the test suite
# and benchmark suite files multiple times - once for each solution. We also
# need to make sure we inject the unique namespace names into each of the
# solutions, to prevent name clashes.

# ------------------------------------------------------------------------------
# Enumerate solutions by poking around in the filesystem
# ------------------------------------------------------------------------------
# Globbing in CMake is normally a terrible idea. And in working with this file
# I discovered many reasons why. We're only globbing so that new solutions can
# be dropped in to the project without needing to update the build scripts.

file(GLOB solution_headers
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/solutions/*.h"
)

set(solution_names)
foreach(solution_header IN LISTS solution_headers)
  file(RELATIVE_PATH
    solution_header_file                  # Output var
    ${CMAKE_CURRENT_SOURCE_DIR}/solutions # Base path
    ${solution_header}                    # Input path
  )
  string(REGEX REPLACE
    "^(.*)\\.h$"                          # Pattern
    "\\1"                                 # Replacement
    solution_name                         # Output var
    "${solution_header_file}"             # Input string
  )
  list(APPEND solution_names ${solution_name})
endforeach()

# ------------------------------------------------------------------------------
function(add_solution_to_lib LIB_NAME SOLUTION_NAME)
  # Add the headers to the library to make them appear in IDEs
  set(header_file ${CMAKE_CURRENT_SOURCE_DIR}/solutions/${SOLUTION_NAME}.h)
  target_sources(${LIB_NAME} PRIVATE
    $<BUILD_INTERFACE:${header_file}>
  )

  set(cpp_file ${CMAKE_CURRENT_SOURCE_DIR}/solutions/${SOLUTION_NAME}.cpp)
  if(EXISTS ${cpp_file})
    target_sources(${LIB_NAME} PRIVATE ${cpp_file})
    set_property(
      SOURCE ${cpp_file}
      PROPERTY COMPILE_DEFINITIONS
        SOLUTION_NAMESPACE=${SOLUTION_NAME}
        SOLUTION_HEADER=\"${header_file}\"
    )
  endif()
endfunction()

# ------------------------------------------------------------------------------
# Build a library containing all of the solution cpp files
# ------------------------------------------------------------------------------
if(solution_names)
  add_library(solutions OBJECT)
  add_library(solutions::solutions ALIAS solutions)

  target_link_libraries(solutions
    PUBLIC
      rangev3::range
      fmt::fmt
  )

  foreach(solution_name IN LISTS solution_names)
    add_solution_to_lib(solutions ${solution_name})
  endforeach()
endif()

# ------------------------------------------------------------------------------
function(add_test_suite_for_solution
    LIB_NAME SOLUTION_NAME TEST_SUITE_FILE SYMLINK_SUFFIX)

  set(header_file ${CMAKE_CURRENT_SOURCE_DIR}/solutions/${SOLUTION_NAME}.h)

  # Make a new symlink to the tests source file for every implementation.
  # We'll provide different compile definitions to each one. The symlink is
  # important so that CMake does not realise that it's the same underlying
  # source file (and thus remove duplicates from the final executable).
  set(symlink_name ${CMAKE_CURRENT_BINARY_DIR}/${SOLUTION_NAME}${SYMLINK_SUFFIX}.cpp)
  add_custom_command(
    OUTPUT ${symlink_name}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${TEST_SUITE_FILE} ${symlink_name}
    DEPENDS ${TEST_SUITE_FILE}
  )

  target_sources(${LIB_NAME} PRIVATE ${symlink_name})

  set_property(
    SOURCE ${symlink_name}
    PROPERTY COMPILE_DEFINITIONS
      SOLUTION_NAMESPACE=${SOLUTION_NAME}
      SOLUTION_NAME_QUOTED=\"${SOLUTION_NAME}\"
      SOLUTION_HEADER=\"${header_file}\"
  )
endfunction()

# ------------------------------------------------------------------------------
# Build an executable containing test cases for all solutions
# ------------------------------------------------------------------------------

add_executable(solution_tests
  ${CMAKE_SOURCE_DIR}/thirdparty/doctest_main.cpp
)

target_link_libraries(solution_tests
  PRIVATE
    $<TARGET_NAME_IF_EXISTS:solutions::solutions>
    doctest::doctest
    fmt::fmt
    rangev3::range
)

foreach(solution_name IN LISTS solution_names)
  add_test_suite_for_solution(
    solution_tests
    ${solution_name}
    ${CMAKE_SOURCE_DIR}/pascals_triangle_tests.cpp
    _tests
  )
endforeach()
