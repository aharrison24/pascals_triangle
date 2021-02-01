#pragma once

#include <pt/iterators.h>

#include <cstdint>
#include <memory>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

namespace detail {

constexpr inline auto RowBeginIndex(uint64_t row) noexcept -> uint64_t {
  return (row * (row + 1)) / 2;
}

auto BuildLookupTable(uint32_t num_rows) -> std::unique_ptr<uint64_t[]>;
}  // namespace detail

class pascals_triangle {
  std::unique_ptr<uint64_t[]> values_;
  uint32_t num_rows_;

 public:
  pascals_triangle(uint32_t num_rows)
      : values_(detail::BuildLookupTable(num_rows)), num_rows_(num_rows) {}

  using cursor = pt::contiguous_row_cursor;
  using iterator = pt::contiguous_row_iterator;

  auto begin() const noexcept -> iterator {
    return iterator(cursor(values_.get()));
  }

  auto end() const noexcept -> iterator {
    return iterator(cursor(values_.get() + detail::RowBeginIndex(num_rows_)));
  }
};

inline auto generate_rows(uint32_t num_rows) -> pascals_triangle {
  return pascals_triangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
