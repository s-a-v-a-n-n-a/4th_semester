#ifndef CHUNKED_MEM_TESTS_HPP
#define CHUNKED_MEM_TESTS_HPP

#include "../Chuncked_mem.hpp"

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
    Container<int, Chunked_mem<16>::type> vector(size, false);

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

} // namespace Trainings::chunked_test 

#endif // CHUNKED_MEM_TESTS_HPP
