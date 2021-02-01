#pragma once

#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

namespace detail {

// Wraps a pair of iterators into a type that can be used with range-for loops
// and range-based algorithms.
//
// Example:
//
// auto range = iter_range(begin_iter, end_iter);
// for (auto val : range) {
//   ...
// }
//
template <typename Iter>
struct iter_range : private std::pair<Iter, Iter> {
  constexpr iter_range(Iter first, Iter second)
      : std::pair<Iter, Iter>(first, second) {}
  constexpr Iter begin() const noexcept { return this->first; }
  constexpr Iter end() const noexcept { return this->second; }
};

// Iterates lazily over the values in a single row of pascal's triangle.
// Values are computed when the iterator is incremented.
//
// Example:
//
// auto it = pascal_column_iterator(4);
// REQUIRE(*it == 1); ++it;
// REQUIRE(*it == 4); ++it;
// REQUIRE(*it == 6); ++it;
// REQUIRE(*it == 4); ++it;
// REQUIRE(*it == 1); ++it;
class pascal_column_iterator {
 public:
  using iterator_category = std::input_iterator_tag;
  using value_type = uint64_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type const*;
  using reference = value_type const&;

  // When default constructed, behaves like an 'end' iterator that compares
  // equal with an exhausted pascal_column_iterator.
  constexpr pascal_column_iterator() = default;

  constexpr explicit pascal_column_iterator(uint32_t row) noexcept
      : row_(row), col_(0) {}

  constexpr value_type const& operator*() const noexcept { return next_value_; }

  constexpr value_type const* operator->() const noexcept {
    return std::addressof(next_value_);
  }

  pascal_column_iterator& operator++() noexcept {
    ++col_;
    next_value_ = next_value_ * (row_ + value_type(1) - col_) / col_;
    return (*this);
  }

  pascal_column_iterator operator++(int) noexcept {
    pascal_column_iterator temp(*this);
    ++(*this);
    return temp;
  }

  friend constexpr bool operator==(pascal_column_iterator const& lhs,
                                   pascal_column_iterator const& rhs) noexcept {
    if (lhs.exhausted() && rhs.exhausted()) {
      return true;
    }
    return std::pair(lhs.row_, lhs.col_) == std::pair(rhs.row_, rhs.col_);
  }

  friend constexpr bool operator!=(pascal_column_iterator const& lhs,
                                   pascal_column_iterator const& rhs) noexcept {
    return !(lhs == rhs);
  }

 private:
  constexpr bool exhausted() const noexcept { return col_ > row_; }

 private:
  value_type row_ = 0;
  value_type col_ =
      1;  // When col_ > row_ the iterator is considered exhausted.
  value_type next_value_ = 1;
};

// Wraps a pair of pascal_column_iterators into a range-like object that
// can be used with a range-for loop.
//
// Example:
//
// // Iterates over all values in row 4 of pascal's triangle
// for (uint64_t val : pascal_column_range(4)) {
//   ...
// }
struct pascal_column_range : iter_range<pascal_column_iterator> {
  constexpr pascal_column_range() noexcept
      : iter_range(pascal_column_iterator(), pascal_column_iterator()) {}
  constexpr pascal_column_range(uint32_t row) noexcept
      : iter_range(pascal_column_iterator(row), pascal_column_iterator()) {}
};

// Iterates lazily over the rows of pascal's triangle. Each row is itself
// a lazy range over the columns/values in the row (represented by a
// pascal_column_range object)
//
// Example:
//
// auto it = pascal_row_iterator(4);
// REQUIRE(*it == pascal_column_range(0)); ++it;
// REQUIRE(*it == pascal_column_range(1)); ++it;
// REQUIRE(*it == pascal_column_range(2)); ++it;
// REQUIRE(*it == pascal_column_range(3)); ++it;
class pascal_row_iterator {
 public:
  using iterator_category = std::input_iterator_tag;
  using value_type = pascal_column_range;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type const*;
  using reference = value_type const&;

  // When default constructed, behaves like an 'end' iterator that compares
  // equal with an exhausted pascal_row_iterator.
  constexpr pascal_row_iterator() = default;

  constexpr explicit pascal_row_iterator(uint32_t num_rows) noexcept
      : num_rows_(num_rows), next_value_(pascal_column_range(0)) {}

  constexpr value_type const& operator*() const noexcept { return next_value_; }

  constexpr value_type const* operator->() const noexcept {
    return std::addressof(next_value_);
  }
  pascal_row_iterator& operator++() noexcept {
    next_value_ = pascal_column_range(++row_);
    return (*this);
  }

  pascal_row_iterator operator++(int) noexcept {
    pascal_row_iterator temp(*this);
    ++(*this);
    return temp;
  }

  friend constexpr bool operator==(pascal_row_iterator const& lhs,
                                   pascal_row_iterator const& rhs) noexcept {
    if (lhs.exhausted() && rhs.exhausted()) {
      return true;
    }
    return std::tie(lhs.num_rows_, lhs.row_) ==
           std::tie(rhs.num_rows_, rhs.row_);
  }

  friend constexpr bool operator!=(pascal_row_iterator const& lhs,
                                   pascal_row_iterator const& rhs) noexcept {
    return !(lhs == rhs);
  }

 private:
  constexpr bool exhausted() const noexcept { return row_ >= num_rows_; }

 private:
  uint32_t num_rows_ = 0;
  uint32_t row_ = 0;  // When row_ >= num_rows_ the iterator is exhausted
  value_type next_value_ = pascal_column_range();
};

// Wraps a pair of pascal_row_iterators into a range-like object that
// can be used with a range-for loop.
//
// Example:
//
// // Iterates over first 4 rows of pascal's triangle
// for (auto row : pascal_row_range(4)) {
//   for (uint64_t val : row) {
//     ...
//   }
// }
struct pascal_row_range : iter_range<pascal_row_iterator> {
  constexpr pascal_row_range() noexcept
      : iter_range(pascal_row_iterator(), pascal_row_iterator()) {}
  constexpr pascal_row_range(uint32_t num_rows) noexcept
      : iter_range(pascal_row_iterator(num_rows), pascal_row_iterator()) {}
};

}  // namespace detail

using pascals_triangle = detail::pascal_row_range;

constexpr inline auto generate_rows(uint32_t num_rows) noexcept
    -> pascals_triangle {
  return pascals_triangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
