#include SOLUTION_HEADER

#include <tbb/tbb.h>

#include <cstdint>
#include <memory>

using namespace tbb;
using namespace SOLUTION_NAMESPACE;

namespace {
void FillRowN(uint64_t* row, uint32_t n) {
  row[0] = 1;
  for (uint32_t k = 1; k < n / 2 + 1; ++k) {  //loop noting symmetry
    row[k] = (row[k - 1] * (n - k)) / k;      //leverage recursive nature of nCk
  }
  std::copy(row, row + n / 2, std::reverse_iterator(row + n));
}

void FillRowBlock(uint64_t* values, const blocked_range<uint32_t>& r) {
  auto* p = values + detail::RowBeginIndex(r.begin());
  for (auto i = r.begin(); i < r.end(); ++i, p += i) {
    FillRowN(p, i + 1);
  }
}
}  // namespace

namespace SOLUTION_NAMESPACE::detail {
auto BuildLookupTable(uint32_t num_rows) -> std::unique_ptr<uint64_t[]> {
  auto values = std::unique_ptr<uint64_t[]>(
      new uint64_t[detail::RowBeginIndex(num_rows)]);

  parallel_for(blocked_range<uint32_t>(0, num_rows),
               [p = values.get()](auto const& r) { FillRowBlock(p, r); });
  return values;
}
}  // namespace SOLUTION_NAMESPACE::detail
