#pragma once

#include <cstdint>
#include <memory>
#include <range/v3/view/span.hpp>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

namespace detail {
class PascalsTriangle {
  std::unique_ptr<uint64_t[]> values_;
  std::vector<ranges::span<uint64_t>> rows_;

 public:
  PascalsTriangle(uint32_t num_rows);

  auto begin() const { return rows_.cbegin(); }
  auto end() const { return rows_.cend(); }
};
}  // namespace detail

inline auto generate_rows(uint32_t num_rows) -> detail::PascalsTriangle {
  return detail::PascalsTriangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
