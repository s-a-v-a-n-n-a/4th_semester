#ifndef SORTS_HPP
#define SORTS_HPP

#include <cstdio>
#include <cstdlib>
#include <algorithm>
// #include <bits/stdc++.h>

#include "Intercepted_int.hpp"

int compare(const void *a, const void *b);
bool cmp(const Intercepted_int &a, const Intercepted_int &b);

void bubble_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));
void selection_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));

// void std_sort(Intercepted_int *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));
// void std_stable_sort(Intercepted_int *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *));

#endif // SORTS_HPP
