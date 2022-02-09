#include "Int_array_delegates.hpp"

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, calling sort functions
// -----------------------------------------------------------------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, calling sort functions and animating his host
// -----------------------------------------------------------------------------------------------------------------------------------

Animating_sort_delegate::Animating_sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)), Visual_object *par_to_animate)
: Sort_delegate(arg_container, arg_sort), Animating(par_to_animate) {}

bool Animating_sort_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
    Sort_delegate::on_mouse_click(par_x, par_y);
    return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_sort_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
    return Animating::on_mouse_move(from, to);
}

bool Animating_sort_delegate::on_mouse_release()
{
    Sort_delegate::on_mouse_release();
    return Animating::on_mouse_release();
}

// -----------------------------------------------------------------------------------------------------------------------------------
// Refill delegate
// -----------------------------------------------------------------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, that refills his container and animates his host
// -----------------------------------------------------------------------------------------------------------------------------------

Animating_refill_delegate::Animating_refill_delegate(Int_container *arg_container, Bar_graph *arg_bar_graph, Visual_object *par_to_animate)
: Refill_delegate(arg_container, arg_bar_graph), Animating(par_to_animate) {}

bool Animating_refill_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
    Refill_delegate::on_mouse_click(par_x, par_y);
    return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_refill_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
    return Animating::on_mouse_move(from, to);
}

bool Animating_refill_delegate::on_mouse_release()
{
    Refill_delegate::on_mouse_release();
    return Animating::on_mouse_release();
}

