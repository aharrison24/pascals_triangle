#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

//----------------------------------------------------------------------------
auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {

  if (num_rows == 0) {
    return {};
  }

  std::vector<std::vector<uint64_t>> triangle_array(
      num_rows, std::vector<uint64_t>(num_rows + 1, 0));

  triangle_array[0][1] = 1;
  for (uint32_t m_i = 1; m_i < num_rows; m_i++) {
    for (uint32_t m_j = 1; m_j < num_rows + 1; m_j++) {
      triangle_array[m_i][m_j] =
          triangle_array[m_i - 1][m_j - 1] + triangle_array[m_i - 1][m_j];
    }
  }

  size_t n_entries = 1;
  for (auto& row : triangle_array) {
    row.erase(std::begin(row));
    row.resize(n_entries);
    n_entries++;
  }

  return triangle_array;
}

}  // namespace SOLUTION_NAMESPACE
