#include "Int_container.hpp"

Int_container::Int_container(size_t amount)
: Int_signal_receiver(), to_contact(nullptr), lowest_id(0)
{
    array = new Intercepted_int[amount];
    lowest_id = array[0].get_id();

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
    size_t id = lowest_id;
    for (size_t i = 0; i < capacity; ++i)
    {
        int num = rand() % 1000 - 500;

        array[i] = num;
        array[i].set_parent(this);

        array[i].set_id(id++);
    }

    length = capacity;
}

void Int_container::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{    
    // Just sending a signal about operation
    if (to_contact)
        to_contact->signal(signal_type, sender, other);
}

Intercepted_int& Int_container::operator[] (const Intercepted_int index)
{
    return array[index.get_num()];
}


