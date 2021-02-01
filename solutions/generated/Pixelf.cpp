#include <cstdint>
#include <future>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

const int MAXIMUM_PASCAL_ROWS_FOR_64_BIT_ARCH = 63;

void FillRowN(std::vector<uint64_t>& row, uint32_t n) {
  row.resize(n);
  *row.begin() = 1;
  for (uint32_t k = 1; k < n / 2 + 1; ++k) {  //loop noting symmetry
    row[k] = (row[k - 1] * (n - k)) / k;      //leverage recursive nature of nCk
  }
  std::copy(row.begin(), row.begin() + n / 2, row.rbegin());
}

void FillRowsInParallel(std::vector<std::vector<uint64_t>>& rows,
                        uint32_t n_rows) {
  rows.resize(n_rows);
  std::vector<std::future<void>> futures;
  for (uint32_t i = 0; i < n_rows; ++i) {
    futures.emplace_back(std::async(FillRowN, std::ref(rows[i]), i + 1));
  }

  for (auto& f : futures) {
    f.get();
  }
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> rows;
  if (num_rows == 0) {
    return rows;
  } else if (num_rows > MAXIMUM_PASCAL_ROWS_FOR_64_BIT_ARCH) {
    throw std::runtime_error("out of range for 64 bit architecture");
  } else {
    FillRowsInParallel(rows, num_rows);  //and we dont need a pyramid
  }
  return rows;
}

}  // namespace SOLUTION_NAMESPACE
