#include "Int_container.hpp"

Int_container::Int_container(size_t amount)
{
    array = new Intercepted_int[amount];

    if (array)
    {
        capacity = amount;
        length = 0;
    }
}

Int_container::~Int_container()
{
    delete [] array;
}

void Int_container::resize()
{
    size_t new_capacity = capacity * 2;
    
    Intercepted_int *other_array = new Intercepted_int[new_capacity];
    for (size_t i = 0; i < length; ++i)
        other_array[i] = array[i];
    delete [] array;

    array = other_array;
    capacity = new_capacity;
}

void Int_container::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    
}


