#ifndef INT_CONTAINER_HPP
#define INT_CONTAINER_HPP

#include "../simple_list/simple_list.hpp"
#include "Intercepted_int.hpp"
#include "Int_signal_types.hpp"

class Int_container
{
private:
    Intercepted_int *array;

    size_t length;
    size_t capacity;

    bool positions_changed;

public:
    Int_container(size_t amount);
    ~Int_container();

    Intercepted_int *get_array() { return array; }

    void resize();

    void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other);

    size_t get_length() const { return length; }
}

#endif // INT_CONTAINER_HPP
