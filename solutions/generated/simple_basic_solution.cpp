#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> vv = {};

  for (uint32_t i = 1; i <= num_rows; ++i) {
    std::vector<uint64_t> row(i);

    for (uint32_t j = 0; j < i; ++j) {
      // first and last elements always 1.
      if (j == 0 || j == i - 1) {
        row.at(j) = 1;
      } else {
        // use a pair of iterators to the previous row.
        auto back_itr = (--vv.end())->begin() + j;
        auto front_itr = back_itr - 1;

        row.at(j) = *front_itr + *back_itr;
      }
    }

    vv.push_back(std::move(row));
  }
  return vv;
}

}  // namespace SOLUTION_NAMESPACE
