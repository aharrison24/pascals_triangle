#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_single_row(std::vector<uint64_t>& vec) -> std::vector<uint64_t> {
  std::vector<uint64_t> single_row;

  single_row.push_back(1);

  // sum values from previous row
  for (uint32_t i = 1; i < vec.size(); ++i) {
    single_row.push_back(vec[i - 1] + vec[i]);
  }

  // add last '1' element to grow the triangle
  single_row.push_back(1);

  return single_row;
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> answer;

  // return empty array for zero edge case
  if (num_rows == 0) {
    return answer;
  }

  // add first element of first row
  answer.emplace_back(std::vector<uint64_t>{1});

  // if num_rows > 1, add more rows to the answer
  for (uint32_t i = 1; i < num_rows; ++i) {
    const std::vector<uint64_t> new_row = generate_single_row(answer[i - 1]);
    answer.emplace_back(new_row);
  }

  return answer;
}

}  // namespace SOLUTION_NAMESPACE
