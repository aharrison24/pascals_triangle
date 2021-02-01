#include <cstdint>
#include <vector>

#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  std::vector<std::vector<uint64_t>> rows(num_rows);
  for (auto row = rows.begin(); row != rows.end(); ++row) {
    *row = std::vector<uint64_t>(
        1u + static_cast<size_t>(std::distance(rows.begin(), row)));
    row->front() = 1u;
    row->back() = 1u;
  }

  if (num_rows < 3) {  // no internal elements to process
    return rows;
  }

  for (auto row = rows.begin() + 2; row != rows.end(); ++row) {
    const auto previous_row = row - 1;
    auto summed_entry = row->begin() + 1;

    adjacent_pair(previous_row->begin(), previous_row->end(),
                  [&summed_entry](const auto trailer, const auto first) {
                    *summed_entry = trailer + first;
                    ++summed_entry;
                  });
  }

  return rows;
}

}  // namespace SOLUTION_NAMESPACE
