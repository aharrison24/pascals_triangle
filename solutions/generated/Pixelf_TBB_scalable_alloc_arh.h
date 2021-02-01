#pragma once

#include <tbb/scalable_allocator.h>

#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

template <typename T>
using scalable_vec = std::vector<T, tbb::scalable_allocator<uint64_t>>;

auto generate_rows(uint32_t num_rows) -> std::vector<scalable_vec<uint64_t>>;

}  // namespace SOLUTION_NAMESPACE
