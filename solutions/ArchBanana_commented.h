#pragma once

#include <cstdint>
#include <range/v3/all.hpp>
#include <vector>

namespace SOLUTION_NAMESPACE {

namespace impl {

// Sum all of the elements in a range.
//
// # Example
//
// REQUIRE(sum(std::vector{1,2,3,4,5}) == 15);
static auto sum = [](auto&& range) -> uint64_t {
  return ranges::accumulate(range, uint64_t(0));
};

// Given a valid row of pascal's triangle, computes the next row in the
// sequence.
//
// # Example
//
// auto result = compute_next_row(std::vector<uint64_t>{1,4,6,4,1});
// auto expected = std::vector<uint64_t>{1,5,10,10,5,1});
// REQUIRE(result == expected);
inline auto compute_next_row(std::vector<uint64_t> const& prev_row)
    -> std::vector<uint64_t> {
  namespace rv = ranges::views;

  // Sum adjacent pairs of internal elements
  // {1, 4, 6, 4, 1} -> {{1,4}, {4,6}, {6,4}, {4,1}} -> {5, 10, 10, 5}
  // prev_row         | sliding(win_size=2)           | transform(sum)
  auto middle = prev_row | rv::sliding(2) | rv::transform(sum);

  // Tack a 1 on to either end of the range and convert to a vector
  // {1} + {5, 10, 10, 5} + {1} -> vector<uint64_t>{1, 5, 10, 10, 5, 1}
  return rv::concat(rv::single(uint64_t(1)), middle, rv::single(uint64_t(1))) |
         ranges::to_vector;
}

}  // namespace impl

// Generates pascal's triangle up to a requested number of rows
//
// # Example
//
// auto result = generate_rows(4);
// auto expected = std::vector<std:vector<uint64_t>>
//   {{1}, {1,1}, {1,2,1}, {1,3,3,1}};
// REQUIRE(result == expected);
inline auto generate_rows(uint32_t num_rows) {
  // On each call, this lambda will return the next row of the triangle.
  // When called, it returns the stored row, and computes one to be stored for
  // next time.
  // REQUIRE(pascal_rows() == {1});
  // REQUIRE(pascal_rows() == {1,1});
  // REQUIRE(pascal_rows() == {1,2,1});
  // etc...
  auto pascal_rows = [stored_row = std::vector<uint64_t>{1}]() mutable {
    return std::exchange(stored_row, impl::compute_next_row(stored_row));
  };

  // Apply generator function the requested number of times
  return ranges::views::generate_n(pascal_rows, num_rows);
}

}  // namespace SOLUTION_NAMESPACE
