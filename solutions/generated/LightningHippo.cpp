#include SOLUTION_HEADER

namespace SOLUTION_NAMESPACE::detail {

constexpr auto triangle_full_impl =
    detail::pascal_lookup_table<max_valid_rows>();

auto const& triangle_full = triangle_full_impl;

}  // namespace SOLUTION_NAMESPACE::detail
