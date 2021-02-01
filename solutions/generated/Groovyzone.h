#pragma once

#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

/**
 * Inspired by Marshall Clow
 * https://www.youtube.com/watch?v=h4Jl1fk3MkQ
 */
template <typename ForwardIter, typename Func>
void adjacent_pair(ForwardIter first, ForwardIter last, Func f) {
  if (first != last) {
    ForwardIter trailer = first;
    ++first;
    for (; first != last; ++first, ++trailer) {
      f(*trailer, *first);
    }
  }
}

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>>;

}  // namespace SOLUTION_NAMESPACE
