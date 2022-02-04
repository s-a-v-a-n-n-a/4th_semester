#include "Sorts_research.hpp"

void count_sort_operations(std::vector<Vector_ll> &vec, std::vector<Intercepted_int*> &data, int start_array_length, size_t operations_amount, int step, Research type, void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
{
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
        // Intercepted_int *array = new Intercepted_int[current_size];

        // randomize array
        // for (int j = 0; j < current_size; ++j)
        // {
        //     long long number = rand() % (1000) - 500;
        //     array[j] = (int)number;
        // }

        sort(data[i], current_size, sizeof(Intercepted_int), compare);

        vec[i].set_x(current_size);
        for (int j = 0; j < current_size; ++j)
        {
            switch (type)
            {
            case Research::ASSIGNMENT:
                vec[i].set_y(vec[i].get_y() + data[i][j].get_assignment_cnt());
                break;
            case Research::COMPARISON:
                vec[i].set_y(vec[i].get_y() + data[i][j].get_comparison_cnt());
                break;
            default:
                break;
            }
        }

        // delete [] array;
    }

    // return vec;
}
