#pragma once

#include <cstdint>

#include "range/v3/all.hpp"

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

inline auto generate_rows(uint32_t num_rows) noexcept {
  return ranges::views::for_each(
      ranges::views::iota(uint32_t{0}, num_rows), [](uint32_t row) {
        return ranges::yield(ranges::views::concat(
            ranges::views::single(uint32_t{1}),
            ranges::views::iota(uint32_t{1}, row + 1) |
                ranges::views::transform(
                    [row, p = uint64_t{1}](uint32_t col) mutable {
                      p = (p * (row - col + 1)) / col;
                      return p;
                    })));
      });
}

}  // namespace SOLUTION_NAMESPACE
