#pragma once
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "range/v3/all.hpp"

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

struct Rows {
  Rows(uint32_t n) { row.reserve(n / 2 + 1); }
  auto operator()() noexcept {
    namespace rv = ranges::views;
    if (size(row) == a) {
      row.push_back(empty(row) ? 1 : row.back());
    } else {
      ++a;
    }
    std::adjacent_difference(begin(row), end(row), begin(row), std::plus<>{});
    return rv::concat(row, row | rv::slice(decltype(a){0}, a) | rv::reverse);
  }
  std::vector<uint64_t> row;
  std::vector<uint64_t>::size_type a = 0;
};

inline auto generate_rows(uint32_t num_rows) noexcept {
  namespace rv = ranges::views;
  return rv::generate_n(Rows{num_rows}, num_rows);
}

}  // namespace SOLUTION_NAMESPACE
