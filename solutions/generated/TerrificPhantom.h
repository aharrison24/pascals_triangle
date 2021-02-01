// ANCHOR: solution
#pragma once

#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>>;

}  // namespace SOLUTION_NAMESPACE
// ANCHOR_END: solution

// -----------------------------------------------------------------------------
// Added by ARH to inform test suite not to try invalid row counts.
namespace SOLUTION_NAMESPACE {
constexpr auto max_rows_to_test() noexcept -> uint32_t {
  return 10;
}
}  // namespace SOLUTION_NAMESPACE
