#include "Sorts_research.hpp"

std::vector<Vector_ll> count_sort_operations(int start_array_length, size_t operations_amount, int step, void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
{
    std::vector<Vector_ll> result(operations_amount, Vector_ll(0, 0));

    int current_size = start_array_length;
    for (size_t i = 0; i < operations_amount; ++i, current_size += step)
    {
        Intercepted_int *array = new Intercepted_int[current_size];

        // randomize array
        for (int j = 0; j < current_size; ++j)
        {
            long long number = rand() % (500) + 1;
            array[j] = (int)number;
        }

        sort(array, current_size, sizeof(Intercepted_int), compare);

        for (int j = 0; j < current_size; ++j)
        {
            result[j].set_x(result[j].get_x() + array[j].get_assignment_cnt());
            result[j].set_y(result[j].get_y() + array[j].get_comparison_cnt());
        }

        delete [] array;
    }

    return result;
}
