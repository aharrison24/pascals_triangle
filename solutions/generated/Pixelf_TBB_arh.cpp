#include SOLUTION_HEADER

#include <tbb/tbb.h>

#include <cstdint>
#include <vector>

using namespace tbb;

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

void FillRowN(std::vector<uint64_t>& row, uint32_t n) {
  row.resize(n);
  *row.begin() = 1;
  for (uint32_t k = 1; k < n / 2 + 1; ++k) {  //loop noting symmetry
    row[k] = (row[k - 1] * (n - k)) / k;      //leverage recursive nature of nCk
  }
  std::copy(row.begin(), row.begin() + n / 2, row.rbegin());
}

void FillRowBlock(std::vector<std::vector<uint64_t>>& rows,
                  const blocked_range<uint32_t>& r) {
  for (auto i = r.begin(); i < r.end(); ++i) {
    FillRowN(rows[i], i + 1);
  }
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> rows(num_rows);
  if (num_rows == 0) {
    return rows;
  }

  {
    parallel_for(blocked_range<uint32_t>(0, num_rows),
                 [&rows](auto const& r) { FillRowBlock(rows, r); });
  }
  return rows;
}

}  // namespace SOLUTION_NAMESPACE
