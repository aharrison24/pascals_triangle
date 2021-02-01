#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

// solution inspired by https://github.com/AceLewis/my_first_calculator.py

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  if (num_rows == 0) {
    return {};
  } else if (num_rows == 1) {
    return {{1}};
  } else if (num_rows == 2) {
    return {{1}, {1, 1}};
  } else if (num_rows == 3) {
    return {{1}, {1, 1}, {1, 2, 1}};
  } else if (num_rows == 4) {
    return {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}};
  } else if (num_rows == 5) {
    return {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};
  } else if (num_rows == 6) {
    return {{1},          {1, 1},          {1, 2, 1},
            {1, 3, 3, 1}, {1, 4, 6, 4, 1}, {1, 5, 10, 10, 5, 1}};
  } else if (num_rows == 7) {
    return {{1},
            {1, 1},
            {1, 2, 1},
            {1, 3, 3, 1},
            {1, 4, 6, 4, 1},
            {1, 5, 10, 10, 5, 1},
            {1, 6, 15, 20, 15, 6, 1}};
  } else if (num_rows == 8) {
    return {{1},
            {1, 1},
            {1, 2, 1},
            {1, 3, 3, 1},
            {1, 4, 6, 4, 1},
            {1, 5, 10, 10, 5, 1},
            {1, 6, 15, 20, 15, 6, 1},
            {1, 7, 21, 35, 35, 21, 7, 1}};
  } else if (num_rows == 9) {
    return {{1},
            {1, 1},
            {1, 2, 1},
            {1, 3, 3, 1},
            {1, 4, 6, 4, 1},
            {1, 5, 10, 10, 5, 1},
            {1, 6, 15, 20, 15, 6, 1},
            {1, 7, 21, 35, 35, 21, 7, 1},
            {1, 8, 28, 56, 70, 56, 28, 8, 1}};
  } else if (num_rows == 10) {
    return {{1},
            {1, 1},
            {1, 2, 1},
            {1, 3, 3, 1},
            {1, 4, 6, 4, 1},
            {1, 5, 10, 10, 5, 1},
            {1, 6, 15, 20, 15, 6, 1},
            {1, 7, 21, 35, 35, 21, 7, 1},
            {1, 8, 28, 56, 70, 56, 28, 8, 1},
            {1, 9, 36, 84, 126, 126, 84, 36, 9, 1}};
  }

  return {};
}

}  // namespace SOLUTION_NAMESPACE
