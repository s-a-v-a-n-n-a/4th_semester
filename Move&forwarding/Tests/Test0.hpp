#ifndef TEST0_HPP
#define TEST0_HPP

#include <memory>

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_container.hpp"
#include "../math_structures/Sorts.hpp"

#include "../Microscope/Int_dumper.hpp"

#include "../Cplusplus_referencing/My_move.hpp"
#include "../Cplusplus_referencing/My_forwarding.hpp"

template<class T>
void imitaion_forward(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_forward<T>(arg);  
}

template<class T>
void imitaion_move(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_move(arg);
}

template<class T>
void imitaion(T& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = arg;
}

template<class T>
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_forward(my_forward<T>(arg)); // the same as it received
    // imitaion_move(arg);
}

// void swap(Intercepted_int &a, Intercepted_int &b) 
// {
//     Intercepted_int tmp = a;
//     a = std::forward<Intercepted_int>(b);
//     b = std::forward<Intercepted_int>(tmp);
// }

void test0()
{
    VAR(a, 20);
    VAR(b, 22);
    // VAR(c, 0);
    // imitaion(a);
    // swap(a, b);
    // imitaion_move(a);
    std::unique_ptr<Intercepted_int> n;

    wrapper(std::forward<std::unique_ptr<Intercepted_int>>(n));
    // wrapper(a);
    // we do not have a right to move it
    // forced move is very very bad
}

#endif // TEST0_HPP
