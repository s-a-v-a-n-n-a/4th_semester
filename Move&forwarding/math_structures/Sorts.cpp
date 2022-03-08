#include "Sorts.hpp"

standartised_sort standartised_sorts[] = 
{
    bubble_sort,
    selection_sort,
    insertion_sort,
    std_sort,
    // std_stable_sort,
    wrapped_merge_sort
};
const int sorts_amount = 5;

int compare(const void *a, const void *b)
{
    if (cmp(*(Intercepted_int*)a, *(Intercepted_int*)b))
        return -1;
    
    // if (*((Intercepted_int*)a) == *((Intercepted_int*)b))
    //     return 0;

    return 1;
}

bool cmp(const Intercepted_int &a, const Intercepted_int &b)
{
    return a < b;
}

void bubble_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    for (Intercepted_int i = 0; i < size; i++)    
    { 
        // Last i elements are already in place 
        for (Intercepted_int j = 0; j < size - i.get_num() - 1; j++) 
            if (((Intercepted_int*)array)[j.get_num() + 1] < ((Intercepted_int*)array)[j.get_num()]) 
            {
                Intercepted_int tmp = ((Intercepted_int*)array)[j.get_num() + 1];
                ((Intercepted_int*)array)[j.get_num() + 1] = ((Intercepted_int*)array)[j.get_num()];
                ((Intercepted_int*)array)[j.get_num()] = tmp;
            } 
    }
}

void selection_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < size - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < size; ++j)
        if (((Intercepted_int*)array)[j] < ((Intercepted_int*)array)[min_idx])
            min_idx = j;
 
        Intercepted_int tmp = ((Intercepted_int*)array)[min_idx];
        ((Intercepted_int*)array)[min_idx] = ((Intercepted_int*)array)[i];
        ((Intercepted_int*)array)[i] = tmp;
    }
}

void insertion_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
	for(int i = 1; i < size; ++i)
    {
		for(int j = i; j > 0 && ((Intercepted_int*)array)[j - 1] > ((Intercepted_int*)array)[j]; --j)
        {
			Intercepted_int tmp = ((Intercepted_int*)array)[j - 1];
			((Intercepted_int*)array)[j - 1] = ((Intercepted_int*)array)[j];
			((Intercepted_int*)array)[j]=tmp;
		}
	}
}

void std_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    std::vector<Intercepted_int> vec;
    for (int i = 0; i < size; ++i)
    {
        vec.push_back(((Intercepted_int*)array)[i]);
    }
    
    // for (int i = 0; i < size; ++i)
    // {
    //     printf("%d ", vec[i].get_num());
    // }
    // printf("\n");
    
    std::sort(vec.begin(), vec.end());

    // for (int i = 0; i < size; ++i)
    // {
    //     printf("%d ", vec[i].get_num());
    // }
    // printf("\n");
}

void std_stable_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    std::vector<Intercepted_int> vec;
    for (int i = 0; i < size; ++i)
    {
        vec.push_back(((Intercepted_int*)array)[i]);
    }
    
    std::stable_sort(vec.begin(), vec.end());
}

void std_qsort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    qsort(array, size, block_size, cmp);
}

void merging_length(Intercepted_int *arr, long long sz_arr_1, long long sz_arr, long long index_to_begin)
{
    long long i = 0;
    long long j = 0;
 
    long long amount = 0;

    long long sz_arr_2 = sz_arr - sz_arr_1;
 
    Intercepted_int* arr_tmp_1 = new Intercepted_int[sz_arr_1];
    Intercepted_int* arr_tmp_2 = new Intercepted_int[sz_arr_2];
 
    for (i = 0; i < sz_arr_1; i++)
    {
        arr_tmp_1[i]  = arr[index_to_begin + i];
    }
 
    for (j = 0; i < sz_arr; i++, j++)
    {
        arr_tmp_2[j] = arr[index_to_begin + i];
    }
 
    i = 0;
    j = 0;
 
    while (i < sz_arr_1 && j < sz_arr_2)
    {
        if (arr_tmp_1[i] < arr_tmp_2[j])
        {
            arr[index_to_begin] = arr_tmp_1[i++];
        }
        else
        {
            arr[index_to_begin]  = arr_tmp_2[j++];
        }
        index_to_begin++;
    }
 
    while (i < sz_arr_1)
    {
        arr[index_to_begin] = arr_tmp_1[i++];
 		index_to_begin++;
    }
 
    while (j < sz_arr_2)
    {
        arr[index_to_begin] = arr_tmp_2[j++];	 
        index_to_begin++;
    }
 
    delete [] arr_tmp_1;
    delete [] arr_tmp_2;
}
 
void merge_sort(Intercepted_int *arr, long long sz_arr, long long index_to_begin, void merging(Intercepted_int *arr, long long sz_arr_1, long long sz_arr, long long index_to_begin))
{
    if (sz_arr <= 1)
        return;
 
    long long sz_part = sz_arr/2;
 
    merge_sort(arr, sz_part, index_to_begin, merging);
    merge_sort(arr, sz_arr - sz_part, index_to_begin + sz_part, merging);
 
    merging(arr, sz_part, sz_arr, index_to_begin);
}

void wrapped_merge_sort(void *array, size_t size, size_t block_size, int (*cmp)(const void *, const void *))
{
    merge_sort((Intercepted_int*)array, size, 0, merging_length);
}

