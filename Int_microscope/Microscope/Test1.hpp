#ifndef TEST1_HPP
#define TEST1_HPP

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_container.hpp"
#include "../math_structures/Sorts.hpp"

#include "Int_dumper.hpp"

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
    // VAR(d, 4);
    
    c = func(a) + foo(b);
    // c = (a + b) * d;
}

#endif // TEST1_HPP
