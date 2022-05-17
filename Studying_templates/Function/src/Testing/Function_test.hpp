#ifndef FUNCTION_TEST_HPP
#define FUNCTION_TEST_HPP

#include <cstdlib>
#include <iostream>

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

void creation_test()
{
    std::cout << "\nTest for creating std::function\n";

    Function<int (char)> func(test_function);
    std::cout << "Result of test_function is " << func(5) << "\n";
}

void assignment_test()
{
    std::cout << "\nTest for assignment std::function\n";
    
    Function<int (char)> func(test_function);
    std::cout << "Result of test_function is " << func(5) << "\n";

    My_functor caller_counter{};
    func = caller_counter;

    std::cout << "Result of caller_counter calling is " << func(5) << "\n";
}

void lambda_test()
{
    std::cout << "\nTest for lambda in std::function\n";

    Function<int (char)> func([](char letter)->int
    {
        return (int)letter;
    });

    std::cout << "Result of lambda calling is " << func('a') << "\n";
}

void lambda_with_capture_test()
{
    std::cout << "\nTest for lambda with capture in std::function\n";

    My_functor caller_counter{};
    Function<int (char)> func([&caller_counter](char add)->int
    {
        return caller_counter(add);
    });

    std::cout << "Result of lambda with capture calling is " << func('a') << "\n";
}

void deduction_creation_test()
{
    std::cout << "\nTest for creating std::function [with deduction]\n";

    Function func(test_function);
    std::cout << "Result of test_function is " << func(5) << "\n";
}

void deduction_assignment_test()
{
    std::cout << "\nTest for assignment std::function [with deduction]\n";
    
    My_functor caller_counter{};
    Function func(caller_counter);
    std::cout << "Result of test_function is " << func(5) << "\n";
}

void deduction_lambda_test()
{
    std::cout << "\nTest for lambda in std::function [with deduction]\n";

    Function func([](char letter)->int
    {
        return (int)letter;
    });

    std::cout << "Result of lambda calling is " << func('a') << "\n";
}

void deduction_lambda_with_capture_test()
{
    std::cout << "\nTest for lambda with capture in std::function [with deduction]\n";

    My_functor caller_counter{};
    Function func([&caller_counter](char add)->int
    {
        return caller_counter(add);
    });

    std::cout << "Result of lambda with capture calling is " << func('a') << "\n";
}

void array_of_functions()
{
    std::cout << "\nTest for array of functions\n\n";


}

#endif // FUNCTION_TEST_HPP
