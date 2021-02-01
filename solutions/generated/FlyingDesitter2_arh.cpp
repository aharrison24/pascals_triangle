#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE::detail {

constexpr auto row_alignment = 32;

static constexpr inline auto row_width(uint64_t row) noexcept -> uint64_t {
  constexpr auto elements_per_alignment = row_alignment / sizeof(uint64_t);
  // Rows are grouped by how many cache lines they need. g is the group index.
  auto const g = row / elements_per_alignment;
  return (g + 1) * elements_per_alignment;
}

static constexpr inline auto row_begin_index(uint64_t row) noexcept
    -> uint64_t {
  constexpr auto elements_per_alignment = row_alignment / sizeof(uint64_t);
  // Rows are grouped by how many cache lines they need. g is the group index.
  auto const g = row / elements_per_alignment;
  auto const row_width = (g + 1) * elements_per_alignment;
  return (2 * row - g * elements_per_alignment) * row_width / 2;
}

PascalsTriangle::PascalsTriangle(uint32_t num_rows)
    : values_(new uint64_t[row_begin_index(num_rows)]) {
  rows_.reserve(num_rows);

  uint64_t* p = values_.get();
  auto row = ranges::span<uint64_t>();
  for (uint32_t i = 0; i < num_rows; p += row_width(i), ++i) {
    auto prev_row = std::exchange(row, ranges::span<uint64_t>(p, i + 1));

    row[0] = 1;
    for (uint32_t j = 1; j < i; ++j) {
      row[j] = prev_row[j - 1] + prev_row[j];
    }
    row[i] = 1;

    rows_.push_back(row);
  }
}

}  // namespace SOLUTION_NAMESPACE::detail
