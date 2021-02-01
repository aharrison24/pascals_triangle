#include SOLUTION_HEADER

#include <tbb/tbb.h>

#include <cstdint>
#include <vector>

using namespace tbb;

namespace {
constexpr auto row_begin_index(uint64_t row) noexcept -> uint64_t {
  return (row * (row + 1)) / 2;
}

void FillRowN(ranges::span<uint64_t> row) {
  auto const n = static_cast<uint32_t>(row.size());
  row[0] = 1;
  for (uint32_t k = 1; k < n / 2 + 1; ++k) {  //loop noting symmetry
    row[k] = (row[k - 1] * (n - k)) / k;      //leverage recursive nature of nCk
  }
  std::copy(row.begin(), row.begin() + n / 2, row.rbegin());
}

[[maybe_unused]] void FillRowBlock(std::vector<ranges::span<uint64_t>>& rows,
                                   uint64_t* values,
                                   const blocked_range<uint32_t>& r) {

  uint64_t* p = values + row_begin_index(r.begin());
  for (auto i = r.begin(); i < r.end(); ++i, p += i) {
    auto row = ranges::span<uint64_t>(p, i + 1);
    FillRowN(row);
    rows[i] = row;
  }
}

}  // namespace

namespace SOLUTION_NAMESPACE::detail {

PascalsTriangle::PascalsTriangle(uint32_t num_rows) {
  if (num_rows == 0) {
    return;
  }

  auto values =
      std::unique_ptr<uint64_t[]>(new uint64_t[row_begin_index(num_rows)]);
  auto rows = std::vector<ranges::span<uint64_t>>(num_rows);

  parallel_for(
      blocked_range<uint32_t>(0, num_rows),
      [&rows, &values](auto const& r) { FillRowBlock(rows, values.get(), r); });

  using std::swap;
  swap(values_, values);
  swap(rows_, rows);
}

}  // namespace SOLUTION_NAMESPACE::detail
