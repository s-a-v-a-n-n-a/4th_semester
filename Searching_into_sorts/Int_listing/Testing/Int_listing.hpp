#ifndef INT_LISTING_HPP
#define INT_LISTING_HPP

#include "../math_structures/Int_signal_receiver.hpp"

extern const char *Signal_names[];

class Int_listing : public Int_signal_receiver
{
private:
    // Int_listing();
    
    void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other) override;
};

#endif // INT_LISTING_HPP
