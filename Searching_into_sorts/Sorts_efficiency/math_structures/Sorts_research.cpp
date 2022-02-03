#include "Sorts_research.hpp"

void count_sort_operations(std::vector<Vector_ll> &vec, int start_array_length, size_t operations_amount, int step, void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
{
    // std::vector<Vector_ll> result(operations_amount, Vector_ll(0, 0));

    // size_t max_size = start_array_length + operations_amount * step;
    size_t vec_size = vec.size();
    int index = 0;
    if (vec_size <= operations_amount)
        for (; index < vec_size; ++index)
        {
            vec[index] = (Vector_ll(0, 0));
        }
    for (; index < operations_amount; ++index)
    {
        vec.push_back(Vector_ll(0, 0));
    }
    
    int current_size = start_array_length;
    for (size_t i = 0; i < operations_amount; ++i, current_size += step)
    {
        Intercepted_int *array = new Intercepted_int[current_size];

        // randomize array
        for (int j = 0; j < current_size; ++j)
        {
            long long number = rand() % (1000) - 500;
            array[j] = (int)number;
        }

        sort(array, current_size, sizeof(Intercepted_int), compare);

        for (int j = 0; j < current_size; ++j)
        {
            vec[i].set_x(vec[i].get_x() + array[j].get_assignment_cnt());
            vec[i].set_y(vec[i].get_y() + array[j].get_comparison_cnt());
        }

        delete [] array;
    }

    // return vec;
}
