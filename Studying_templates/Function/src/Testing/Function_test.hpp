#ifndef FUNCTION_TEST_HPP
#define FUNCTION_TEST_HPP

#include <cstdlib>
#include <iostream>

#include "../Function/Function.hpp"

int test_function(char element) 
{
    return element * 2;
}

void creation_test()
{
    std::cout << "Test for creating std::function\n";

    Function<int (char)> func(test_function);
    std::cout << "Result of test_fucntion is " << func(5) << "\n";
}

#endif // FUNCTION_TEST_HPP
