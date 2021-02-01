#pragma once

#include <cstdint>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>>;

auto generate_single_row(std::vector<uint64_t>& vec) -> std::vector<uint64_t>;

}  // namespace SOLUTION_NAMESPACE
