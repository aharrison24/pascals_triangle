#pragma once

#include <array>
#include <cstdio>
#include <vector>

namespace SOLUTION_NAMESPACE {  // Please do not modify this line

template <int N>
struct Factorial {
  enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0> {
  enum { value = 1 };
};

/**
 * Variadic template for a recursive helper struct.
 */
template <int TABLE_SIZE, int INDEX = 0, int... D>
struct Helper : Helper<TABLE_SIZE,
                       INDEX + 1,
                       D...,
                       Factorial<TABLE_SIZE - 1>::value /
                           (Factorial<TABLE_SIZE - 1 - INDEX>::value *
                            Factorial<INDEX>::value)> {};

/**
 * Specialization of the template to end the recursion when the table size reaches TABLE_SIZE.
 */
template <int TABLE_SIZE, int... D>
struct Helper<TABLE_SIZE, TABLE_SIZE, D...> {
  static constexpr std::array<int, TABLE_SIZE> table = {D...};
};

constexpr std::array<int, 1> table1 = Helper<1>::table;
constexpr std::array<int, 2> table2 = Helper<2>::table;
constexpr std::array<int, 3> table3 = Helper<3>::table;
constexpr std::array<int, 4> table4 = Helper<4>::table;
constexpr std::array<int, 5> table5 = Helper<5>::table;
constexpr std::array<int, 6> table6 = Helper<6>::table;
constexpr std::array<int, 7> table7 = Helper<7>::table;
constexpr std::array<int, 8> table8 = Helper<8>::table;
constexpr std::array<int, 9> table9 = Helper<9>::table;
constexpr std::array<int, 10> table10 = Helper<10>::table;

std::vector<std::vector<uint64_t>> result = {
    std::vector<uint64_t>(table1.begin(), table1.end()),
    std::vector<uint64_t>(table2.begin(), table2.end()),
    std::vector<uint64_t>(table3.begin(), table3.end()),
    std::vector<uint64_t>(table4.begin(), table4.end()),
    std::vector<uint64_t>(table5.begin(), table5.end()),
    std::vector<uint64_t>(table6.begin(), table6.end()),
    std::vector<uint64_t>(table7.begin(), table7.end()),
    std::vector<uint64_t>(table8.begin(), table8.end()),
    std::vector<uint64_t>(table9.begin(), table9.end()),
    std::vector<uint64_t>(table10.begin(), table10.end()),
};

auto generate_rows(uint32_t num_rows) -> std::vector<std::vector<uint64_t>> {
  return std::vector<std::vector<uint64_t>>(result.begin(),
                                            result.begin() + num_rows);
}

}  // namespace SOLUTION_NAMESPACE
