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
    Intercepted_int const *sender_addrss = &sender;
    Intercepted_int const *other_addrss = &other;
    
    // Checking if sender's and other's ids belong to array that is sorted by us
    if (signal_type == Int_signal::ASSIGN && 
        sender.get_id() >= lowest_id && sender.get_id() < lowest_id + length &&
        other.get_id() >= lowest_id && other.get_id() < lowest_id + length)
    {
        // Just sending a signal about operation
        if (to_contact)
            to_contact->signal(signal_type, sender, other);
    }
}


