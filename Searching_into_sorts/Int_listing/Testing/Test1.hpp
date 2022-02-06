#ifndef TEST1_HPP
#define TEST1_HPP

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Int_container.hpp"
#include "../math_structures/Sorts.hpp"

#include "Int_listing.hpp"

void test1()
{
    Int_listing *listing_object = new Int_listing();
    
    Int_container *container = new Int_container(50);
	container->random_fill();
	container->set_contact(listing_object);

    bubble_sort(container->get_array(), container->get_length(), sizeof(Intercepted_int), compare);
}

#endif // TEST1_HPP
