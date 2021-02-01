#pragma once

#include <blaze/Math.h>
#include <blaze/math/Subvector.h>

#include <cstdint>
#include <range/v3/algorithm/generate_n.hpp>
#include <range/v3/view/generate_n.hpp>
#include <range/v3/view/span.hpp>

namespace SOLUTION_NAMESPACE {

namespace impl {

inline auto compute_next_row(uint32_t row_index,
                             blaze::DynamicVector<uint64_t> const& prev_row,
                             blaze::DynamicVector<uint64_t>& output) noexcept
    -> void {
  using namespace blaze;

  auto const lhs = subvector<aligned>(prev_row, 0, row_index);
  auto const rhs = subvector<unaligned>(prev_row, 1, row_index);
  auto dest = subvector<unaligned>(output, 1, row_index);

  dest = lhs + rhs;

  output[row_index] = 1;
}

class pascals_triangle {
  blaze::DynamicVector<uint64_t> row_curr_;
  blaze::DynamicVector<uint64_t> row_next_;
  uint32_t row_index_{0};

 public:
  explicit pascals_triangle(uint32_t num_rows)
      : row_curr_(num_rows + 1), row_next_(num_rows + 1) {
    row_curr_[0] = 1;
    row_next_[0] = 1;
  }

  auto next_row() noexcept {
    blaze::swap(row_curr_, row_next_);
    compute_next_row(++row_index_, row_curr_, row_next_);
    return ranges::span<uint64_t>(row_curr_.data(), row_index_);
  }
};

}  // namespace impl

inline auto generate_rows(uint32_t num_rows) {
  return ranges::views::generate_n(
      [triangle = impl::pascals_triangle(num_rows)]() mutable {
        return triangle.next_row();
      },
      num_rows);
}

}  // namespace SOLUTION_NAMESPACE
