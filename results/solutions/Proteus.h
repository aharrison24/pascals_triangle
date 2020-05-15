#pragma once

#include SOLUTION_HEADER

#include <algorithm>
#include <cassert>
#include <range/v3/all.hpp>
#include <vector>

namespace SOLUTION_NAMESPACE {

namespace detail {

class PascalRow {
  std::vector<uint64_t> row_values_;
  int row_ = 0;

 public:
  explicit PascalRow(uint32_t num_rows) : row_values_(num_rows + 1, 0) {
    row_values_[0] = 1;
  }

  // Compute values for next row and return them as an iterable range.
  // Invalidates all existing iterators returned by begin and end.
  auto operator()() noexcept -> PascalRow const& {
    assert(row_ < static_cast<int>(row_values_.size()));

    // Compute new values in-place by summing pairs of previous values.
    // Work backwards to avoid overwriting values before we've used them.
    auto row_end = next(row_values_.begin(), row_ + 1);
    auto const input_begin = std::reverse_iterator(row_end);
    auto const input_end = std::reverse_iterator(next(row_values_.begin()));
    auto const output_begin = std::reverse_iterator(row_end);

    std::transform(input_begin, input_end,  // First input range
                   next(input_begin),       // Second input range
                   output_begin,            // Output range
                   std::plus<>{});

    ++row_;
    return *this;
  }

  auto begin() const noexcept { return cbegin(row_values_); }
  auto end() const noexcept { return next(cbegin(row_values_), row_); }
};

}  // namespace detail

inline auto generate_rows(uint32_t num_rows) {
  using ranges::views::generate_n;
  return generate_n(detail::PascalRow(num_rows), num_rows);
}

}  // namespace SOLUTION_NAMESPACE
