#include "Int_array_delegates.hpp"

Sort_delegate::Sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
: Button_delegate(), array_container(arg_container), sort(arg_sort) {}

bool Sort_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Sort_delegate::on_mouse_release()
{
    sort(array_container->get_array(), array_container->get_length(), sizeof(Int_container), compare);

    return true;
}

Refill_delegate::Refill_delegate(Int_container *arg_container, Bar_graph *arg_bar_graph)
: Button_delegate(), array_container(arg_container), bar_graph(arg_bar_graph) {}

bool Refill_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Refill_delegate::on_mouse_release()
{
    array_container->random_fill();
    bar_graph->synchronize();

    return true;
}

