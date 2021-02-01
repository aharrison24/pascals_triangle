#pragma once

#include <boost/container/pmr/monotonic_buffer_resource.hpp>
#include <boost/container/pmr/vector.hpp>
#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line
namespace pmr = boost::container::pmr;

class pascals_triangle {
  pmr::monotonic_buffer_resource res_;
  std::vector<pmr::vector<uint64_t>> rows_;

 public:
  pascals_triangle(uint32_t num_rows);

  auto begin() const noexcept { return rows_.begin(); }
  auto end() const noexcept { return rows_.end(); }
};

inline auto generate_rows(uint32_t num_rows) -> pascals_triangle {
  return pascals_triangle(num_rows);
}

}  // namespace SOLUTION_NAMESPACE
