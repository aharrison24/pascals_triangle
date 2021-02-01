#pragma once

#include <cstdint>
#include <range/v3/all.hpp>
#include <vector>

namespace SOLUTION_NAMESPACE {

namespace impl {
static auto sum = [](auto&& range) -> uint64_t {
  return ranges::accumulate(range, uint64_t(0));
};

inline auto compute_next_row(std::vector<uint64_t> const& prev_row)
    -> std::vector<uint64_t> {
  namespace rv = ranges::views;
  auto middle = prev_row | rv::sliding(2) | rv::transform(sum);
  return rv::concat(rv::single(uint64_t(1)), middle, rv::single(uint64_t(1))) |
         ranges::to_vector;
}

}  // namespace impl

inline auto generate_rows(uint32_t num_rows) {
  auto pascal_rows = [stored_row = std::vector<uint64_t>{1}]() mutable {
    return std::exchange(stored_row, impl::compute_next_row(stored_row));
  };

  return ranges::views::generate_n(pascal_rows, num_rows);
}

}  // namespace SOLUTION_NAMESPACE
