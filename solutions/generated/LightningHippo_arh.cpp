#include SOLUTION_HEADER

#include <pt/algorithms.h>

#include <range/v3/view/span.hpp>

namespace SOLUTION_NAMESPACE::detail {

namespace {
// -----------------------------------------------------------------------------
// Compute values of a row, given the previous row
constexpr void compute_next_row(ranges::span<uint64_t const> prev_row,
                                ranges::span<uint64_t> next_row) {
  assert(next_row.size() == prev_row.size() + 1);

  next_row.front() = 1;

  // Sum adjacent elements from the previous row.
  pt::transform_adjacent_pairs(prev_row.begin(),      // Input begin
                               prev_row.end(),        // Input end
                               next_row.begin() + 1,  // Output begin
                               std::plus<>{});

  next_row.back() = 1;
}

// -----------------------------------------------------------------------------
// Stores a lookup table of pascal triangle rows.
// Can be constructed at compile time if required.
// -----------------------------------------------------------------------------
template <uint32_t max_rows>
struct pascal_lookup_table {
  constexpr pascal_lookup_table() noexcept {
    auto next_row = ranges::span(values.begin(), 0);

    while (next_row.size() < max_rows) {
      auto prev_row = pt::exchange(
          next_row, ranges::span(next_row.end(), next_row.size() + 1));

      compute_next_row(prev_row, next_row);
    }
  }

  std::array<uint64_t, num_elements_total(max_rows)> values{};
};

// Compute pascals triangle at compile time. We're doing this inside a separate
// translation unit so that the work only needs to get done once.
constexpr auto triangle_full = pascal_lookup_table<max_rows>();
}  // namespace

// Make the computed values available to other translation units
std::array<uint64_t, num_elements_total(max_rows)> const& triangle_values =
    triangle_full.values;

}  // namespace SOLUTION_NAMESPACE::detail
