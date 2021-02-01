#pragma once

#include <cstdint>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/generate_n.hpp>
#include <range/v3/view/sliding.hpp>
#include <range/v3/view/span.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>

namespace SOLUTION_NAMESPACE {

namespace impl {
static auto sum = [](auto&& range) noexcept -> uint64_t {
  return ranges::accumulate(range, uint64_t(0));
};

template <typename InputRange, typename OutputIter>
inline void compute_next_row(InputRange&& prev_row, OutputIter out) noexcept {
  namespace rv = ranges::views;
  auto const middle = prev_row | rv::sliding(2) | rv::transform(sum);
  ranges::copy(middle, out + 1);
}

class pascals_triangle {
  std::vector<uint64_t> prev_buffer_;
  std::vector<uint64_t> curr_buffer_;
  int64_t curr_row_len_{0};

 public:
  explicit pascals_triangle(uint32_t num_rows)
      : prev_buffer_(num_rows + 1, 1), curr_buffer_(num_rows + 1, 1) {}

  auto next_row() noexcept {
    ranges::swap(prev_buffer_, curr_buffer_);
    auto prev_row = ranges::span(prev_buffer_.data(), curr_row_len_);
    auto next_row = ranges::span(curr_buffer_.data(), ++curr_row_len_);

    compute_next_row(prev_row, curr_buffer_.begin());

    return next_row;
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
