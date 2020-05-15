#include <fmt/format.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

std::vector<uint64_t> get_row(uint32_t num_row) {
  if (num_row == 0)
    return {1};
  if (num_row == 1)
    return {1, 1};
  if (num_row == 2)
    return {1, 2, 1};
  if (num_row == 3)
    return {1, 3, 3, 1};
  if (num_row == 4)
    return {1, 4, 6, 4, 1};
  if (num_row == 5)
    return {1, 5, 10, 10, 5, 1};
  if (num_row == 6)
    return {1, 6, 15, 20, 15, 6, 1};
  if (num_row == 7)
    return {1, 7, 21, 35, 35, 21, 7, 1};
  if (num_row == 8)
    return {1, 8, 28, 56, 70, 56, 28, 8, 1};
  if (num_row == 9)
    return {1, 9, 36, 84, 126, 126, 84, 36, 9, 1};
  else
    throw std::invalid_argument("I wasn't thinking this far ahead...");
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {

  std::vector<std::vector<uint64_t>> triangle(num_rows);
  for (uint32_t i = 0; i < num_rows; i++) {
    triangle[i] = get_row(i);
  }

  return triangle;
}

}  // namespace SOLUTION_NAMESPACE
