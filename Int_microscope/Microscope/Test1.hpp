#ifndef TEST1_HPP
#define TEST1_HPP

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_container.hpp"
#include "../math_structures/Sorts.hpp"

#include "Int_dumper.hpp"

Intercepted_int secret_func()
{
    Spy spy(__FUNCTION__); // RAII

    VAR(in_secret, 128);
    return in_secret;
}

Intercepted_int func(const Intercepted_int &var)
{
    Spy spy(__FUNCTION__); // RAII
    
    return var;
}

Intercepted_int foo(const Intercepted_int &var)
{
    Spy spy(__FUNCTION__); // RAII
    
    return func(var);
}

Intercepted_int sum(const Intercepted_int &var1, const Intercepted_int &var2)
{
    Spy spy(__FUNCTION__); // RAII

    return var1 + var2;
}

void test0()
{
    VAR(a, 20);
    VAR(b, 22);
    VAR(c, 0);
    
    c = sum(a, b);
}

#endif // TEST1_HPP
