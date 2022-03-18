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
void container_push_imitaion(T arg) 
{
    Spy spy(__FUNCTION__);
    
    // like writing into container
    volatile auto local_tmp = arg;
}

template< class T >
void wrapper(T&& arg) 
{
    Spy spy(__FUNCTION__);
    
    container_push_imitaion(my_forward<T>(arg));
}

void test0()
{
    // VAR(a, 20);
    
    // printf("variable a: %d\n", a.get_num());
    // container_push_imitaion(a);
    // printf("variable a after \"safe\" function: %d\n", a.get_num());

    wrapper(Intercepted_int(20));

    // printf("variable a after wrapper: %d\n", a.get_num());
}
#endif // TEST0_HPP
