#ifndef INT_SIGNAL_RECEIVER_HPP
#define INT_SIGNAL_RECEIVER_HPP

#include "Int_signal_types.hpp"
#include "Intercepted_int.hpp"

class Intercepted_int;

class Int_signal_receiver
{
public:
    virtual void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other) {}
};

#endif // INT_SIGNAL_RECEIVER_HPP
