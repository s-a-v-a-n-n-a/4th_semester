#ifndef SORTS_HPP
#define SORTS_HPP

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "Intercepted_int.hpp"

int compare(const void *a, const void *b);
bool cmp(const Intercepted_int &a, const Intercepted_int &b);

void bubble_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));
void selection_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));

void std_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));
void std_stable_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));

void wrapped_merge_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));
void merging_length(Intercepted_int *arr, long long sz_arr_1, long long sz_arr, long long index_to_begin);
void merge_sort(Intercepted_int *arr, long long sz_arr, long long index_to_begin, void merging(Intercepted_int *arr, long long sz_arr_1, long long sz_arr, long long index_to_begin));

#endif // SORTS_HPP
