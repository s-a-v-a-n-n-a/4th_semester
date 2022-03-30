#ifndef STATIC_MEM_TESTS_HPP
#define STATIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"

namespace Trainings::static_test 
{

void for_bool()
{
    const size_t size = 10;
    Container<bool, Static_mem<2>::type> vector;

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
    Container<int, Static_mem<size>::type> vector;

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

// void test_no_construct()
// {
    
// }


} // Trainings::static_test

#endif // STATIC_MEM_TESTS_HPP
