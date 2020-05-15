#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> rows;
  std::vector<uint64_t> previous_row;

  while (rows.size() < num_rows) {
    std::vector<uint64_t> new_row;
    uint64_t previous_element = 0;
    for (const auto element : previous_row) {
      new_row.push_back(previous_element + element);
      previous_element = element;
    }

    new_row.push_back(1);
    rows.push_back(new_row);
    previous_row = new_row;
  }
  return rows;
}

}  // namespace SOLUTION_NAMESPACE
