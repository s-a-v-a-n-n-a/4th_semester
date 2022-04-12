#ifndef STATIC_MEM_TESTS_HPP
#define STATIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"
#include "../Storages/Static_mem.hpp"

namespace Trainings::static_test 
{

void for_bool()
{
    printf("\nTesting static bool storage\n\n\n");
    
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
    printf("\nTesting static int storage\n\n\n");
    
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

void for_iterator()
{
    printf("\nTesting static int storage for iterator\n\n\n");

    const size_t size = 10;
    Container<int, Static_mem<size>::type> vector;
    
    for (size_t i = 0; i < size; ++i)
    {
        vector[i] = i;
    }
    
    for (auto i = vector.begin(); i < vector.end(); ++i)
    {
        printf("%d ", *i);
    }
    printf("\n");
}

void for_range_based_for()
{
    printf("\nTesting static int storage for range based for\n\n\n");

    const size_t size = 7;
    Container<int, Static_mem<size>::type> vector{0, 1, 2, 4, 8, 16, 32};
    
    for (auto i : vector)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void for_std_find()
{
    printf("\nTesting static int storage for std::find\n\n\n");

    const size_t size = 7;
    Container<int, Static_mem<size>::type> vector{0, 1, 2, 4, 8, 16, 32};

    printf("found %d\n", *(std::find(vector.begin(), vector.end(), 16)));
}

void for_std_copy()
{
    printf("\nTesting static int storage for std::copy\n\n\n");

    const size_t size = 7;
    Container<int, Static_mem<size>::type> vector_from{0, 1, 2, 4, 8, 16, 32};
    Container<int, Static_mem<size>::type> vector_to;

    std::copy(vector_from.begin(), vector_from.end(), vector_to.begin());

    for (auto i = vector_to.begin(); i < vector_to.end(); ++i)
    {
        printf("%d ", *i);
    }
    printf("\n");
}

} // Trainings::static_test

#endif // STATIC_MEM_TESTS_HPP
