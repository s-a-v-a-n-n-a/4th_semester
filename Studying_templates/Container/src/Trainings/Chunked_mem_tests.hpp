#ifndef CHUNKED_MEM_TESTS_HPP
#define CHUNKED_MEM_TESTS_HPP

#include "../Container/Container.hpp"
#include "../Storages/Chunked_mem.hpp"

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

void test_no_construct()
{
    const size_t size = 10;
    Container<No_default_constructor, Chunked_mem<16>::type> vector(size, 0);
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

void for_iterator()
{
    printf("\nTesting chunked int storage for iterator\n\n\n");

    const size_t size = 30;
    Container<int, Chunked_mem<8>::type> vector(size, 0);
    
    for (auto i = vector.begin(); i < vector.end(); ++i)
    {
        printf("%d ", *i);
    }
    printf("\n");
}

void for_initial_element()
{
    printf("\nTesting chunked int storage for constructing with initial element\n\n\n");

    Container<int, Chunked_mem<8>::type> vector(10, 4);

    vector[5] = 0;

    for (int i = 0; i < 10; ++i)
    {
        vector.push_back(i);
    }

    for (auto i : vector)
    {
        printf("%d ", i);
    }
    printf("\n");

}

void for_initial_element_and_resize()
{
    printf("\nTesting chunked int storage for constructing with initial element\n\n\n");

    Container<int, Chunked_mem<8>::type> vector(10, 4);

    vector.resize(50, 9);

    for (auto i : vector)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void for_resize_down()
{
    printf("\nTesting chunked int storage for resizing down\n\n\n");

    Container<int, Chunked_mem<8>::type> vector(50, 9);

    vector.resize(20, 4);

    for (auto i : vector)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void for_range_based_for()
{
    printf("\nTesting chunked int storage for range based for\n\n\n");

    Container<int, Chunked_mem<16>::type> vector;
    size_t power = 2;
    for (size_t i = 0; i < 35; ++i)
    {
        vector.push_back(power);
        power *= 2;
    }
    
    for (auto i : vector)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void for_std_find()
{
    printf("\nTesting chunked int storage for std::find\n\n\n");

    Container<int, Chunked_mem<8>::type> vector;
    size_t power = 2;
    for (size_t i = 0; i < 35; ++i)
    {
        vector.push_back(power);
        power *= 2;
    }

    printf("found %d\n", *(std::find(vector.begin(), vector.end(), 16)));
}

void for_std_copy()
{
    printf("\nTesting chunked int storage for std::copy\n\n\n");

    Container<int, Chunked_mem<8>::type> vector_from;
    size_t power = 2;
    for (size_t i = 0; i < 35; ++i)
    {
        vector_from.push_back(power);
        power *= 2;
    }
    Container<int, Dynamic_mem> vector_to(vector_from.size(), 0);

    std::copy(vector_from.begin(), vector_from.end(), vector_to.begin());

    for (auto i = vector_to.begin(); i < vector_to.end(); ++i)
    {
        printf("%d ", *i);
    }
    printf("\n");
}

} // namespace Trainings::chunked_test 

#endif // CHUNKED_MEM_TESTS_HPP
