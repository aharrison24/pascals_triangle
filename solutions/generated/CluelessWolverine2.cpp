#include <cmath>
#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> triangle;
  triangle.reserve(num_rows);

  for (uint32_t i = 0; i < num_rows; i++) {
    // Create row, pre-sized, all 1s.
    std::vector<uint64_t> row(i + 1, 1);

    for (uint32_t j = 1; j < (i + 2) / 2; j++) {
      // Compute each non-1 entry and assign to both sides of triangle
      row[j] = row[i - j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
    }

    // Add to full triangle
    triangle.push_back(std::move(row));
  }

  return triangle;
}

}  // namespace SOLUTION_NAMESPACE
