// ANCHOR: solution
#pragma once

#include <pt/algorithms.h>
#include <pt/iterators.h>

#include <array>
#include <cstdint>

namespace SOLUTION_NAMESPACE {
namespace detail {

constexpr auto num_elements_total(uint64_t num_rows) -> uint64_t {
  return (num_rows * (num_rows + 1)) / 2;
}

// Computes a lookup table of pascal triangle rows, that can be constructed at
// compile time if required.
template <uint32_t max_rows>
struct pascal_lookup_table {
  constexpr pascal_lookup_table() noexcept {
    pt::fill(values.begin(), values.end(), 1ULL);

    uint64_t* p = values.begin() + 1;  // Beginning of row
    for (uint32_t row = 1; row < max_rows; ++row, p += row) {
      pt::transform_adjacent_pairs(p - row,  // Input begin
                                   p,        // Input end
                                   p,        // Output
                                   std::plus<>{});
    }
  }

  std::array<uint64_t, num_elements_total(max_rows)> values{0};
};

constexpr uint32_t max_valid_rows = 63;
extern pascal_lookup_table<max_valid_rows> const& triangle_full;

}  // namespace detail

inline auto generate_rows(uint32_t num_rows) noexcept {
  num_rows = std::min(num_rows, detail::max_valid_rows);

  // table has static lifetime, so won't ever dangle.
  auto const& table = detail::triangle_full.values;

  return pt::make_pascal_table_range(                       //
      table.begin(),                                        //
      table.begin() + detail::num_elements_total(num_rows)  //
  );
}

}  // namespace SOLUTION_NAMESPACE
// ANCHOR_END: solution

// -----------------------------------------------------------------------------
// Added by ARH to inform test suite not to try invalid row counts.
namespace SOLUTION_NAMESPACE {
constexpr auto max_rows_to_test() noexcept -> uint32_t {
  return detail::max_valid_rows;
}
}  // namespace SOLUTION_NAMESPACE
