#include "Int_array_delegates.hpp"

Sort_delegate::Sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
: Button_delegate(), array_container(arg_container), sort(arg_sort) {}

bool Sort_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Sort_delegate::on_mouse_release()
{
    printf("Sorting\n");
    sort(array_container->get_array(), array_container->get_length(), sizeof(Int_container), compare);

    return true;
}


