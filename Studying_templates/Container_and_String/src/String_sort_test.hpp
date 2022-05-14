#ifndef STRING_SORT_TEST_HPP
#define STRING_SORT_TEST_HPP

#include <algorithm>

#include "../../Container/src/Container/Container.hpp"
#include "../../Container/src/Storages/Dynamic_mem.hpp"

#include "../../My_string/src/String/String.hpp"
#include "../../My_string/src/Allocators/Allocator.hpp"

using Char_string = String<char, Zeroing_allocator>;

void string_sort_test()
{   
    std::cout << "Testing String and Container together: std::sort on vector of strings\n\n";
    
    Container<Char_string, Dynamic_mem> vector{ "First string", "Second string", "Third string", "Forth string", "ABC" };

    std::sort(vector.begin(), vector.end());

    for (size_t idx = 0; idx < vector.size(); ++idx)
    {
        std::cout << vector[idx] << " ";
    }
    std::cout << "\n";
}

#endif // STRING_SORT_TEST_HPP
