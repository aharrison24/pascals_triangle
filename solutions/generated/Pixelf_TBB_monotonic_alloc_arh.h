#pragma once

#include <pt/allocators.h>

#include <cstdint>
#include <vector>

namespace pt {
template <typename T>
using vector = std::vector<T, pt::MonotonicAllocator<T>>;
}

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

class pascals_triangle {
  pt::MonotonicBufferResource res_;
  std::vector<pt::vector<uint64_t>> rows_;

 public:
  pascals_triangle(uint32_t num_rows);

  auto begin() const noexcept { return rows_.begin(); }
  auto end() const noexcept { return rows_.end(); }
};

inline auto generate_rows(uint32_t num_rows) -> pascals_triangle {
  return pascals_triangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
