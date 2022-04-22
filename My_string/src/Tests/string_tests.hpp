#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP

#include <cstdio>

#include "../String/String.hpp"

void creation_test()
{
    String<char> string("It works", 4);

    for (size_t idx = 0; idx < string.size(); ++idx)
    {
        printf("%c\n", string[idx]);
    }
}

#endif // STRING_TESTS_HPP
