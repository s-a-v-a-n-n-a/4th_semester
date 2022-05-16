#ifndef MY_FORWARDING_HPP
#define MY_FORWARDING_HPP

#include "Referencing.hpp"

template<class T>
T&& my_forward(typename unreferenced_type<T>::type& a)
{
    return static_cast<T&&>(a);
}

template<class T>
T&& my_forward(typename unreferenced_type<T>::type&& a)
{
    return static_cast<T&&>(a);
}

#endif // MY_FORWARDING_HPP
