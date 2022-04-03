#ifndef CHUNKED_MEM_TESTS_HPP
#define CHUNKED_MEM_TESTS_HPP

#include "../Container/Chuncked_mem.hpp"

namespace Trainings::chunked_test 
{

void for_bool()
{
    const size_t size = 10;
    Container<bool, Chunked_mem<16>::type> vector(size, 0);

    for (size_t i = 0; i < size; ++i)
    {
        if (i % 2)
            vector[i] = true;
        else
            vector[i] = false;
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (vector[i])
            printf("true ");
        else
            printf("false ");
    }
    printf("\n");
}

void for_int()
{
    const size_t size = 10;
    Container<int, Chunked_mem<16>::type> vector(size, 0);

    for (size_t i = 0; i < size; ++i)
    {
        vector[i] = i;
    }

    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void for_resize()
{
    const size_t size = 100;
    Container<double, Chunked_mem<16>::type> vector(size, 0.0);

    for (size_t i = 0; i < 75; ++i)
    {
        vector[i] = i;
    }

    printf("capacity: %zu\n", vector.capacity());

    vector.resize(50);

    printf("capacity after resize: %zu, size after resize: %zu\n", vector.capacity(), vector.size());

    for (size_t idx = 0; idx < 25; ++idx)
    {
        vector.pop_back();
    }

    printf("capacity after popping back: %zu, size after popping back: %zu\n", vector.capacity(), vector.size());

    vector.shrink_to_fit();

    printf("capacity after shrink_to_fit: %zu, size after shrink_to_fit: %zu\n", vector.capacity(), vector.size());

    size_t vec_size = vector.size();
    for (size_t idx = 0; idx < vec_size; ++idx)
    {
        printf("%f ", vector[idx]);
    }
    printf("\n");
}

} // namespace Trainings::chunked_test 

#endif // CHUNKED_MEM_TESTS_HPP
