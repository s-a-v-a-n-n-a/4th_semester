#ifndef STATIC_MEM_TESTS_HPP
#define STATIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"

void static_test_bool()
{
    Container<bool, 10, Static_mem> vector;

    for (size_t i = 0; i < 10; ++i)
    {
        if (i % 2)
            vector[i] = true;
        else
            vector[i] = false;
    }
}

#endif // STATIC_MEM_TESTS_HPP
