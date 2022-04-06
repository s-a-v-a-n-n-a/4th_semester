#ifndef DYNAMIC_MEM_TESTS_HPP
#define DYNAMIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"

#include "../Types/No_default_constructor/No_default_constructor.hpp"

namespace Trainings::dynamic_test
{

void for_int()
{
    printf("\nTesting dynamic int storage\n\n\n");
    
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

void for_initializer_list()
{
    printf("\nTesting dynamic int storage: initializer_list\n\n\n");
    
    const size_t size = 10;
    Container<int, Dynamic_mem> vector{0, 1, 2, 4, 8, 16, 32};

    for (size_t i = 0; i < vector.size(); ++i)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void for_bool()
{
    printf("\nTesting dynamic bool storage\n\n\n");
    
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
    printf("\nTesting dynamic storage for type without default constructor\n\n\n");
    
    const size_t size = 10;
    Container<No_default_constructor, Dynamic_mem> vector(size, 0);
}

void for_resize()
{
    printf("\nTesting dynamic double storage resizing\n\n\n");
    
    const size_t size = 100;
    Container<double, Dynamic_mem> vector(size, 0.0);

    for (size_t i = 0; i < 75; ++i)
    {
        vector[i] = i;
    }

    printf("capacity: %zu, size: %zu\n", vector.capacity(), vector.size());

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

void for_iterator()
{
    printf("\nTesting dynamic int storage for iterator\n\n\n");

    const size_t size = 10;
    Container<int, Dynamic_mem> vector(size, 0);
    
    for (auto i = vector.begin(); i < vector.end(); ++i)
    {
        printf("%d ", *i);
    }
}

} // Trainings/dynamic_test

#endif // DYNAMIC_MEM_TESTS_HPP
