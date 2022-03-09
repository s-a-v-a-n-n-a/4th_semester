#ifndef TEST0_HPP
#define TEST0_HPP

#include <memory>

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_container.hpp"
#include "../math_structures/Sorts.hpp"

#include "../Microscope/Int_dumper.hpp"

#include "../Cplusplus_referencing/My_move.hpp"
#include "../Cplusplus_referencing/My_forwarding.hpp"

template< class T >
void imitaion_with_forward(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = my_forward<T>(arg);
}

template< class T >
void imitaion(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = arg;
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    imitaion_with_forward(my_forward<T>(arg)); // or just `imitation(arg);` in other case
}

void test0()
{
    wrapper(Intercepted_int(20));
}
#endif // TEST0_HPP
