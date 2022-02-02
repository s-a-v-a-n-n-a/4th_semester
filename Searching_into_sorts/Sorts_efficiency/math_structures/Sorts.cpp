#include "Sorts.hpp"

int compare(const void *a, const void *b)
{
    return (*(Intercepted_int*)a - *(Intercepted_int*)b).get_num();
}

bool cmp(const Intercepted_int &a, const Intercepted_int &b)
{
    if (compare(&a, &b) < 0)
        return true;

    return false;
}

void bubble_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < size; i++)    
    { 
        // Last i elements are already in place 
        for (int j = 0; j < size - i - 1; j++) 
            if (((Intercepted_int*)array)[j + 1] < ((Intercepted_int*)array)[j]) 
            {
                Intercepted_int tmp = ((Intercepted_int*)array)[j + 1];
                ((Intercepted_int*)array)[j + 1] = ((Intercepted_int*)array)[j];
                ((Intercepted_int*)array)[j] = tmp;
            } 
    }
}

void selection_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < size; j++)
        if (((Intercepted_int*)array)[j] < ((Intercepted_int*)array)[min_idx])
            min_idx = j;
 
        Intercepted_int tmp = ((Intercepted_int*)array)[min_idx];
        ((Intercepted_int*)array)[min_idx] = ((Intercepted_int*)array)[i];
        ((Intercepted_int*)array)[i] = tmp;
    }
}

// void std_sort(Intercepted_int *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
// {
//     std::sort(array, (void*)(array + size));
// }

// void std_stable_sort(Intercepted_int *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
// {
//     std::stable_sort(array, (void*)(array + size));
// }
