#ifndef DYNAMIC_MEM_TESTS_HPP
#define DYNAMIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"

#include "../Types/No_default_constructor/No_default_constructor.hpp"

namespace Trainings::dynamic_test
{

void for_int()
{
    const size_t size = 10;
    Container<int, Dynamic_mem> vector(size, 0);

    for (size_t i = 0; i < size; ++i)
    {
        vector[i] = i;
    }

    for (size_t i = 0; i < size; ++i)
    {
        vector.push_back(i + size);
    }

    for (size_t i = 0; i < 2 * size; ++i)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void for_bool()
{
    const size_t size = 10;
    Container<bool, Dynamic_mem> vector(size, false);

    for (size_t i = 0; i < size; ++i)
    {
        if (i % 2)
            vector[i] = true;
        else
            vector[i] = false;
    }

    for (size_t i = 0; i < size; ++i)
    {
        vector.push_back(true);
    }

    for (size_t i = 0; i < 2 * size; ++i)
    {
        if (vector[i])
            printf("true ");
        else
            printf("false ");
    }
    printf("\n");
}

void test_no_construct()
{
    const size_t size = 10;
    Container<No_default_constructor, Dynamic_mem> vector(size, 0);
}

} // Trainings/dynamic_test

#endif // DYNAMIC_MEM_TESTS_HPP
