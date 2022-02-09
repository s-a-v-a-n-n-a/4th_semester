#ifndef INT_ARRAY_DELEGATES_HPP
#define INT_ARRAY_DELEGATES_HPP

#include "../GUI/Button_delegate.hpp"

#include "../math_structures/Sorts.hpp"
#include "../math_structures/Int_container.hpp"

#include "Graphical_delegates.hpp"
#include "Bar_graph.hpp"

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, calling sort functions
// -----------------------------------------------------------------------------------------------------------------------------------

class Sort_delegate : virtual public Button_delegate
{
private:
    Int_container *array_container;
    void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *));
	
public:
    Sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)));

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, calling sort functions and animating his host
// -----------------------------------------------------------------------------------------------------------------------------------

class Animating_sort_delegate : public Sort_delegate, public Animating
{
public:
    Animating_sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)), Visual_object *par_to_animate);

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
    bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_release() override;
};

// -----------------------------------------------------------------------------------------------------------------------------------
// Refill delegate
// -----------------------------------------------------------------------------------------------------------------------------------

class Refill_delegate : virtual public Button_delegate
{
private:
    Int_container *array_container;
    Bar_graph *bar_graph;
	
public:
    Refill_delegate(Int_container *arg_container, Bar_graph *arg_bar_graph);

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// -----------------------------------------------------------------------------------------------------------------------------------
// Delegate, that refills his container and animates his host
// -----------------------------------------------------------------------------------------------------------------------------------

class Animating_refill_delegate : public Refill_delegate, public Animating
{
public:
    Animating_refill_delegate(Int_container *arg_container, Bar_graph *arg_bar_graph, Visual_object *par_to_animate);

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
    bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_release() override;
};

#endif // INT_ARRAY_DELEGATES_HPP
