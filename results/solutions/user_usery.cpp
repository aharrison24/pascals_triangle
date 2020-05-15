#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

void BuildNewRowWithoutStartAndEndElements(
    const std::vector<uint64_t> &previous_row, std::vector<uint64_t> &new_row) {

  if (previous_row.size() <= 1) {
    return;
  } else {
    for (size_t i = 0; i < previous_row.size(); i++) {
      if ((i + 1) < previous_row.size()) {
        new_row[i + 1] = previous_row[i] + previous_row[i + 1];
      }
    }
  }
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {

  std::vector<std::vector<uint64_t>> solution;

  if (num_rows == 0) {
    return solution;
  }

  // Resize everything to avoid multiple reallocations.
  solution.resize(num_rows);
  for (size_t i = 0; i < num_rows; i++) {
    // Resize each row with the number of elemenets that it will hold.
    solution[i].resize(i + 1);
  }

  // Adding the first row to the solution.
  // We know that we will need at least one row.
  solution[0] = {1};

  for (size_t row_idx = 1; row_idx < num_rows; row_idx++) {
    BuildNewRowWithoutStartAndEndElements(solution[row_idx - 1],
                                          solution[row_idx]);
    solution[row_idx][0] = 1;
    solution[row_idx][solution[row_idx].size() - 1] = 1;
  }

  return solution;
}

}  // namespace SOLUTION_NAMESPACE
