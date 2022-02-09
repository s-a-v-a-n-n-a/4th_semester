#include "Int_container.hpp"

const int MAX_VALUE = 500;
const int MIN_VALUE = -500;

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
    int min = MIN_VALUE < 0 ? -1 * MIN_VALUE : MIN_VALUE;
    
    size_t id = lowest_id;
    for (size_t i = 0; i < capacity; ++i)
    {
        int num = rand() % (MAX_VALUE + min) - MAX_VALUE;

        array[i] = num;
        array[i].set_parent(this);

        array[i].set_id(id++);
    }

    length = capacity;
}

void Int_container::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{    
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


