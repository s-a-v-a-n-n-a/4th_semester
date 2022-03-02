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

Intercepted_int func(Intercepted_int var)
{
    Spy spy(__FUNCTION__); // RAII
    
    return var;
}

Intercepted_int foo(Intercepted_int var)
{
    Spy spy(__FUNCTION__); // RAII
    
    return func(var);
}

void test0()
{
    VAR(a, 20);
    VAR(b, 22);
    VAR(c, 0);
    
    c = func(a) + secret_func();// foo(b);
}

#endif // TEST1_HPP
