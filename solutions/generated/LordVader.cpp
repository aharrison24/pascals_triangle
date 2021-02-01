#include <cassert>
#include <cstdint>
#include <functional>
#include <numeric>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

namespace {

auto generate_next_row(std::vector<uint64_t> const& last_row)
    -> std::vector<uint64_t> {
  std::vector<uint64_t> new_row;
  new_row.reserve(last_row.size() + 1);

  // Find the pairwise sums of the elements in the last row and add to the new row.
  std::adjacent_difference(std::cbegin(last_row), std::cend(last_row),
                           std::back_inserter(new_row), std::plus<>{});
  new_row.push_back(1);  // Add final 1.

  return new_row;
};

}  // namespace

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  assert(num_rows >= 0);

  if (num_rows == 0) {
    return {};
  }

  auto rows = std::vector<std::vector<uint64_t>>{{1}};
  rows.reserve(num_rows);

  for (uint32_t i = 1; i < num_rows; ++i) {
    rows.push_back(generate_next_row(rows[i - 1]));
  }

  return rows;
}

}  // namespace SOLUTION_NAMESPACE
