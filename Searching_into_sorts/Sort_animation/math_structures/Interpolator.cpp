#include "Interpolator.hpp"

void merging_length(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin)
{
    long long i = 0;
    long long j = 0;
 
    long long amount = 0;
 
    Vector_d* arr_tmp_1 = new Vector_d[sz_arr_1];
    Vector_d* arr_tmp_2 = new Vector_d[sz_arr - sz_arr_1];
 
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
 
    while (i < sz_arr_1 && j < sz_arr - sz_arr_1)
    {
        if (arr_tmp_1[i].get_x() < arr_tmp_2[j].get_x())
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
        arr[index_to_begin]  = arr_tmp_1[i++];
 		index_to_begin++;
    }
 
    while (j < sz_arr - sz_arr_1)
    {
        arr[index_to_begin] = arr_tmp_2[j++];	 
        index_to_begin++;
    }
 
    delete [] arr_tmp_1;
    delete [] arr_tmp_2;
}
 
void merge_sort(std::vector<Vector_d> &arr, long long sz_arr, long long index_to_begin, void merging(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin))
{
    if (sz_arr <= 1)
        return;
 
    long long sz_part = sz_arr/2;
 
    merge_sort(arr, sz_part, index_to_begin, merging);
    merge_sort(arr, sz_arr - sz_part, index_to_begin + sz_part, merging);
 
    merging(arr, sz_part, sz_arr, index_to_begin);
}
