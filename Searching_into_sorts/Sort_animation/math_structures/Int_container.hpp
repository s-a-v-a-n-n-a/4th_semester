#ifndef INT_CONTAINER_HPP
#define INT_CONTAINER_HPP

#include "../simple_list/simple_list.hpp"
#include "Intercepted_int.hpp"
#include "Int_signal_types.hpp"

#include "Int_signal_receiver.hpp"

class Int_container : public Int_signal_receiver
{
private:
    Intercepted_int *array;

    size_t length;
    size_t capacity;

    Int_signal_receiver *to_contact;

    size_t lowest_id;

public:
    Int_container(size_t amount);
    ~Int_container();

    void random_fill();

    Intercepted_int *get_array() { return array; }
    size_t get_length() const { return length; }

    size_t get_lowest_id() const { return lowest_id; }

    void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other) override;
    void set_contact(Int_signal_receiver *contact) { to_contact = contact; }

};

#endif // INT_CONTAINER_HPP
