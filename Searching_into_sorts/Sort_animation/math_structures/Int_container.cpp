#include "Int_container.hpp"

Int_container::Int_container(size_t amount)
: Int_signal_receiver(), to_contact(nullptr)
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

void Int_container::random_fill()
{
    for (size_t i = length; i < capacity; ++i)
    {
        int num = rand() % 1000 - 500;

        array[i] = num;
        array[i].set_parent(this);
    }

    length = capacity;
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
    printf("Got a signal\n");
    
    Intercepted_int const *sender_addrss = &sender;
    Intercepted_int const *other_addrss = &other;

    if (signal_type == Int_signal::ASSIGN && sender_addrss >= array && sender_addrss < array + length)
    {
        // отправить запрос на перерисовку
        if (to_contact)
            to_contact->signal(signal_type, sender, other);
    }
}


