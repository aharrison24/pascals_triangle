#include SOLUTION_HEADER

#include <tbb/tbb.h>

#include <algorithm>
#include <cstdint>

using namespace tbb;

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

constexpr auto RowBeginIndex(uint64_t row) noexcept -> uint64_t {
  return (row * (row + 1)) / 2;
}

void FillRowN(pt::vector<uint64_t>& row, uint32_t n) {
  row.resize(n);
  row[0] = 1;
  for (uint32_t k = 1; k < n / 2 + 1; ++k) {  //loop noting symmetry
    row[k] = (row[k - 1] * (n - k)) / k;      //leverage recursive nature of nCk
  }
  std::copy(row.begin(), row.begin() + n / 2, row.rbegin());
}

void FillRowBlock(std::vector<pt::vector<uint64_t>>& rows,
                  const blocked_range<uint32_t>& r) {
  for (auto i = r.begin(); i < r.end(); ++i) {
    FillRowN(rows[i], i + 1);
  }
}

pascals_triangle::pascals_triangle(uint32_t num_rows)
    : res_(RowBeginIndex(num_rows) * sizeof(uint64_t)) {

  auto rows =
      std::vector<pt::vector<uint64_t>>(num_rows, pt::vector<uint64_t>(&res_));
  for (uint32_t i = 0; i < num_rows; ++i) {
    rows[i].reserve(i + 1);
  }

  parallel_for(blocked_range<uint32_t>(0, num_rows),
               [&rows](auto const& r) { FillRowBlock(rows, r); });

  rows_ = std::move(rows);
}

}  // namespace SOLUTION_NAMESPACE
