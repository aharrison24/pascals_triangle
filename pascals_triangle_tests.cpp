#include <doctest/doctest.h>
#include <fmt/format.h>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>

#include SOLUTION_HEADER

// -----------------------------------------------------------------------------
// Test output helpers
// -----------------------------------------------------------------------------
namespace {
namespace rv = ranges::views;

template <typename T>
auto print_vec(std::vector<T> const& row) {
  return fmt::format("{{{}}}", fmt::join(row, ", "));
}

// Collect range of ranges into a vector of vectors
template <typename Range>
auto to_vec_of_vec(Range&& range) -> std::vector<std::vector<uint64_t>> {
  return range | rv::transform(ranges::to_vector) | ranges::to_vector;
};
}  // namespace

// Tell doctest how to print a vector of vectors
namespace doctest {
template <typename T>
struct StringMaker<std::vector<std::vector<T>>> {
  static String convert(std::vector<std::vector<T>> const& value) {
    auto row_strings = value | rv::transform(print_vec<T>);
    return fmt::format("\n{{{}}}\n", fmt::join(row_strings, ",\n")).c_str();
  }
};
}  // namespace doctest

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------
using SOLUTION_NAMESPACE::generate_rows;

#define EXPAND(x) x
TEST_SUITE_BEGIN(EXPAND(SOLUTION_NAME_QUOTED));

TEST_CASE("0 rows") {
  auto const result = to_vec_of_vec(generate_rows(0));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {};
  REQUIRE(result == expected);
}
TEST_CASE("1 row") {
  auto const result = to_vec_of_vec(generate_rows(1));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1}};
  REQUIRE(result == expected);
}
TEST_CASE("2 rows") {
  auto const result = to_vec_of_vec(generate_rows(2));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1}, {1, 1}};
  REQUIRE(result == expected);
}
TEST_CASE("3 rows") {
  auto const result = to_vec_of_vec(generate_rows(3));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1}, {1, 1}, {1, 2, 1}};
  REQUIRE(result == expected);
}
TEST_CASE("4 rows") {
  auto const result = to_vec_of_vec(generate_rows(4));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}};
  REQUIRE(result == expected);
}
TEST_CASE("7 rows") {
  auto const result = to_vec_of_vec(generate_rows(7));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1},
       {1, 1},
       {1, 2, 1},
       {1, 3, 3, 1},
       {1, 4, 6, 4, 1},
       {1, 5, 10, 10, 5, 1},
       {1, 6, 15, 20, 15, 6, 1}};
  REQUIRE(result == expected);
}
TEST_CASE("8 rows") {
  auto const result = to_vec_of_vec(generate_rows(8));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1},
       {1, 1},
       {1, 2, 1},
       {1, 3, 3, 1},
       {1, 4, 6, 4, 1},
       {1, 5, 10, 10, 5, 1},
       {1, 6, 15, 20, 15, 6, 1},
       {1, 7, 21, 35, 35, 21, 7, 1}};
  REQUIRE(result == expected);
}
TEST_CASE("10 rows") {
  auto const result = to_vec_of_vec(generate_rows(10));
  auto const expected = std::vector<std::vector<uint64_t>>  //
      {{1},
       {1, 1},
       {1, 2, 1},
       {1, 3, 3, 1},
       {1, 4, 6, 4, 1},
       {1, 5, 10, 10, 5, 1},
       {1, 6, 15, 20, 15, 6, 1},
       {1, 7, 21, 35, 35, 21, 7, 1},
       {1, 8, 28, 56, 70, 56, 28, 8, 1},
       {1, 9, 36, 84, 126, 126, 84, 36, 9, 1}};
  REQUIRE(result == expected);
}
TEST_SUITE_END();
