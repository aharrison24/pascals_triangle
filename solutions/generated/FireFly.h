// ANCHOR: solution
#pragma once

#include <cstdint>
#include <range/v3/all.hpp>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

class pascals_triangle : public ranges::view_facade<pascals_triangle> {
 public:
  friend ranges::range_access;
  pascals_triangle() = default;
  pascals_triangle(uint64_t end_row) : end_size_(end_row + 1) {}

  auto read() const { return ranges::make_subrange(begin_, begin_ + size_); }
  void next() { begin_ += size_++; }
  bool equal(const pascals_triangle& other) const {
    return size_ == other.size_;
  }
  bool equal(ranges::default_sentinel_t) const { return size_ == end_size_; }

 private:
  uint64_t size_{1};
  uint64_t end_size_{1};
  const uint64_t* begin_{values};

  static const uint64_t values[];
};

inline auto generate_rows(uint64_t num_rows) {
  return pascals_triangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
// ANCHOR_END: solution

// -----------------------------------------------------------------------------
// Added by ARH to inform test suite not to try invalid row counts.
namespace SOLUTION_NAMESPACE {
constexpr auto max_rows_to_test() noexcept -> uint32_t {
  return 10;
}
}  // namespace SOLUTION_NAMESPACE
