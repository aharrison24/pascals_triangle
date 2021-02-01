#include SOLUTION_HEADER

#include <cstdint>
#include <vector>

namespace {
constexpr auto row_begin_index(uint64_t row) noexcept -> uint64_t {
  return (row * (row + 1)) / 2;
}
}  // namespace

namespace SOLUTION_NAMESPACE::detail {

PascalsTriangle::PascalsTriangle(uint32_t num_rows)
    : values_(new uint64_t[row_begin_index(num_rows)]) {
  rows_.reserve(num_rows);

  uint64_t* p = values_.get();
  auto row = ranges::span<uint64_t>();
  for (uint32_t i = 0; i < num_rows; ++i, p += i) {
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
