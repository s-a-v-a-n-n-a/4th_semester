#ifndef ARRAY_OF_FUNCTIONS_TEST_HPP
#define ARRAY_OF_FUNCTIONS_TEST_HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../Container/src/Container/Container.hpp"
#include "../../Container/src/Storages/Dynamic_mem.hpp"

#include "../../Function/src/Function/Function.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------ Helping structures ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int test_function_x2(char element) 
{
    return element * 2;
}

int test_function_x3(char element) 
{
    return element * 3;
}

int test_function_x4(char element) 
{
    return element * 4;
}

int test_function_x5(char element) 
{
    return element * 5;
}

int test_function_x6(char element) 
{
    return element * 6;
}

class My_functor
{
private:
    int called{0};

public:
    int operator() (char add)
    {
        int result = called;

        called += add;
        return result;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------ Test(s) -----------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void array_of_functions()
{   
    std::cout << "Testing Function and Container together: just array of functions\n\n";

    Container<Function<int (char)>, Dynamic_mem> vector{ test_function_x2, test_function_x3, test_function_x4, test_function_x5, test_function_x6 };
    
    for (size_t idx = 0; idx < vector.size(); ++idx)
    {
        std::cout << vector[idx](5) << " "; 
    }
    std::cout << "\n";

    My_functor caller_counter{};
    vector[2] = caller_counter;
    vector[4] = ([](char argument) -> int
    {
        return 42;
    });

    for (auto func : vector)
    {
        std::cout << func(5) << " "; 
    }
    std::cout << "\n";
}

#endif // ARRAY_OF_FUNCTIONS_TEST_HPP
