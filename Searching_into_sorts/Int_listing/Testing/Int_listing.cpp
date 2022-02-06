#include "Int_listing.hpp"

const char *Signal_names[] = 
{
    "+",
    "+=",
    "prefix increment",
    "postfix increment",
    "-",
    "-=",
    "prefix decrement",
    "postfix decrement",
    "*",
    "*=",
    "/",
    "/=",
    "=",
    ">",
    ">=",
    "<",
    "<=",
    "==",
    "!="
};

// Int_listing::Int_listing()
// : Int_signal_receiver() {}

void Int_listing::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    printf("Operation %s on int %d by address %p with int %d by address %p\n", Signal_names[(int)signal_type], sender.get_num(), &sender, other.get_num(), &other);
}

