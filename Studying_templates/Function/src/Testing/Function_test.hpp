#ifndef FUNCTION_TEST_HPP
#define FUNCTION_TEST_HPP

#include <cstdlib>
#include <iostream>

#include "../Function/Function.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------ Helping structures ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int test_function_x2(char element) 
{
    return element * 2;
}

class My_functor
{
private:
    int called_{0};

public:
    My_functor(int initial)
    : called_(initial)
    {}

    int operator() (char add)
    {
        int result = called_;

        called_ += add;
        return result;
    }
};

My_functor my_functor_constructor(char element) 
{
    return My_functor(element);
}

int pluss(int a, int b) {
    return a + b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------ Test(s) -----------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void creation_test()
{
    std::cout << "\n-------------------------------\n";
    std::cout << "Test for creating std::function";
    std::cout << "\n-------------------------------\n";

    Function<int (char)> func(test_function_x2);
    std::cout << "Result of test_function is " << func(5) << "\n";
}

void assignment_test()
{
    std::cout << "\n---------------------------------\n";
    std::cout << "Test for assignment std::function";
    std::cout << "\n---------------------------------\n";
    
    Function<int (char)> func(test_function_x2);
    std::cout << "Result of test_function is " << func(5) << "\n";

    My_functor caller_counter{0};
    func = caller_counter;

    std::cout << "Result of caller_counter calling is " << func(5) << "\n";
}

void lambda_test()
{
    std::cout << "\n--------------------------------\n";
    std::cout << "Test for lambda in std::function";
    std::cout << "\n--------------------------------\n";

    Function<int (char)> func([](char letter)->int
    {
        return (int)letter;
    });

    std::cout << "Result of lambda calling is " << func('a') << "\n";
}

void lambda_with_capture_test()
{
    std::cout << "\n---------------------------------------------\n";
    std::cout << "Test for lambda with capture in std::function";
    std::cout << "\n---------------------------------------------\n";

    My_functor caller_counter{0};
    Function<int (char)> func([&caller_counter](char add)->int
    {
        return caller_counter(add);
    });

    std::cout << "Result of lambda with capture calling is " << func('a') << "\n";
}

void deduction_creation_test()
{
    std::cout << "\n------------------------------------------------\n";
    std::cout << "Test for creating std::function [with deduction]";
    std::cout << "\n------------------------------------------------\n";

    Function func(test_function_x2);
    std::cout << "Result of test_function is " << func(5) << "\n";

    Function class_func(my_functor_constructor);
    My_functor functor = func(5);
    std::cout << "Result of class_func is " << functor(1) << "\n";
}

void deduction_assignment_test()
{
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Test for assignment std::function [with deduction]";
    std::cout << "\n--------------------------------------------------\n";
    
    My_functor caller_counter{0};
    Function func(caller_counter);
    std::cout << "Result of test_function is " << func(5) << "\n";
}

void deduction_lambda_test()
{
    std::cout << "\n-------------------------------------------------\n";
    std::cout << "Test for lambda in std::function [with deduction]";
    std::cout << "\n-------------------------------------------------\n";

    Function func([](char letter)->int
    {
        return (int)letter;
    });

    std::cout << "Result of lambda calling is " << func('a') << "\n";
}

void deduction_lambda_with_capture_test()
{
    std::cout << "\n--------------------------------------------------------------\n";
    std::cout << "Test for lambda with capture in std::function [with deduction]";
    std::cout << "\n--------------------------------------------------------------\n";

    My_functor caller_counter{0};
    Function func([&caller_counter](char add)->int
    {
        return caller_counter(add);
    });

    std::cout << "Result of lambda with capture calling is " << func('a') << "\n";
}

void assign_test()
{
    std::cout << "\n--------------------\n";
    std::cout << "Test for assign test";
    std::cout << "\n--------------------\n";

    Function func([](char letter)->int
    {
        return (int)letter;
    });

    std::cout << "Result of lambda calling is " << func('a') << "\n";

    func.assign(test_function_x2);

    std::cout << "Result of test_function calling is " << func('a') << "\n";
}

void target_test()
{
    std::cout << "\n----------------------\n";
    std::cout << "Test for method target";
    std::cout << "\n----------------------\n";

    Function<int(int, int)> arg = std::plus<int>();
    if (arg.target<std::plus<int>>())
    {
        std::cout << "it is plus\n";
    }
    else 
    {   
        std::cout << "It is not a plus\n";
    }
}

#endif // FUNCTION_TEST_HPP
