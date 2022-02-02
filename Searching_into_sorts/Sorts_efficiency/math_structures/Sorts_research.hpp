#ifndef SORTS_RESEARCH_HPP
#define SORTS_RESEARCH_HPP

#include <vector>
#include <climits>
#include <algorithm>

#include "Intercepted_int.hpp"
#include "Sorts.hpp"
#include "Radius_vector.hpp"

std::vector<Vector_ll> count_sort_operations(int start_array_length, size_t operations_amount, int step, void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)));

#endif // SORTS_RESEARCH_HPP
