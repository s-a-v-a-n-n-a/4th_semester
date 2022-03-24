#ifndef DYNAMIC_MEM_TESTS_HPP
#define DYNAMIC_MEM_TESTS_HPP

#include "../Container/Container.hpp"

void dynamic_test_bool()
{
    Container<bool, 10, Dynamic_mem> vector;

    for (size_t i = 0; i < 10; ++i)
    {
        if (i % 2)
            vector[i] = true;
        else
            vector[i] = false;
    }

    for (size_t i = 0; i < 10; ++i)
    {
        vector.push_back(true);
    }
}


#endif // DYNAMIC_MEM_TESTS_HPP
