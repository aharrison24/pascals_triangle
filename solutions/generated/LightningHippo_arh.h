// ANCHOR: solution
#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <range/v3/view/subrange.hpp>
#include <range/v3/view_facade.hpp>

namespace SOLUTION_NAMESPACE {
namespace detail {

// -----------------------------------------------------------------------------
// Compute number of elements in a triangle of a given number of rows
constexpr auto num_elements_total(uint64_t num_rows) -> uint64_t {
  return (num_rows * (num_rows + 1)) / 2;
}

// -----------------------------------------------------------------------------
constexpr uint32_t max_rows = 63;
extern std::array<uint64_t, num_elements_total(max_rows)> const&
    triangle_values;

// -----------------------------------------------------------------------------
// A lightweight view onto the rows of a pre-computed triangle that is stored
// in a single contiguous array.
// -----------------------------------------------------------------------------
class pascals_triangle : public ranges::view_facade<pascals_triangle> {
  uint64_t const* begin_;
  int64_t num_rows_;
  int64_t row_ = 0;

 public:
  pascals_triangle() = default;
  pascals_triangle(uint64_t const* first, uint32_t num_rows)
      : begin_(first), num_rows_(num_rows) {}

  auto read() const { return ranges::make_subrange(begin_, begin_ + row_ + 1); }
  void next() {
    ++row_;
    begin_ += row_;
  }
  bool equal(const pascals_triangle& other) const {
    return begin_ == other.begin_;
  }
  bool equal(ranges::default_sentinel_t) const { return row_ >= num_rows_; }
};

}  // namespace detail

inline auto generate_rows(uint32_t num_rows) noexcept
    -> detail::pascals_triangle {
  assert(num_rows <= detail::max_rows);

  return detail::pascals_triangle(detail::triangle_values.begin(), num_rows);
}

}  // namespace SOLUTION_NAMESPACE
// ANCHOR_END: solution

// -----------------------------------------------------------------------------
// Added by ARH to inform test suite not to try invalid row counts.
namespace SOLUTION_NAMESPACE {
constexpr auto max_rows_to_test() noexcept -> uint32_t {
  return detail::max_rows;
}
}  // namespace SOLUTION_NAMESPACE
