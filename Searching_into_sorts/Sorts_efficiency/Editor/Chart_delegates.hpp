#ifndef CHART_DELEGATES_HPP
#define CHART_DELEGATES_HPP

#include "Graphical_delegates.hpp"
#include "Chart_window.hpp"

#include "../GUI/Button_delegate.hpp"
#include "../GUI/Visual_object_base.hpp"

#include "../math_structures/Sorts_research.hpp"

// Generate graph delegate
// ----------------------------------------------------------------------------------------------------------------

class Generate_chart : virtual public Button_delegate
{
private:
	Chart_window *field;
    Color color;

    void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *));
	Research type;

public:
	Generate_chart(Chart_window *arg_field, const Color &arg_color, Research arg_type, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)));

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// ----------------------------------------------------------------------------------------------------------------

// Animating generating graph delegate
// ----------------------------------------------------------------------------------------------------------------

class Animating_generate_graph : public Generate_chart, public Animating
{
public:
	Animating_generate_graph(Chart_window *arg_field, const Color &arg_color, Research arg_type, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)), Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_release() override;
};

// ----------------------------------------------------------------------------------------------------------------
// Clear field delegate
// ----------------------------------------------------------------------------------------------------------------

class Clear_field : virtual public Button_delegate
{
private:
	Chart_window *field;

public:
	Clear_field(Chart_window *arg_field);

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// ----------------------------------------------------------------------------------------------------------------
// Animating_clear field delegate
// ----------------------------------------------------------------------------------------------------------------

class Animating_clear_field : public Clear_field, public Animating
{
public:
	Animating_clear_field(Chart_window *arg_field, Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_release() override;
};

// ----------------------------------------------------------------------------------------------------------------
// Regenerating data delegate
// ----------------------------------------------------------------------------------------------------------------

class Regenerate_data : virtual public Button_delegate
{
public:
	Regenerate_data();

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// ----------------------------------------------------------------------------------------------------------------
// Animating regenerating data delegate
// ----------------------------------------------------------------------------------------------------------------

class Animating_regenerate_data : public Regenerate_data, public Animating
{
public:
	Animating_regenerate_data(Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_release() override;
};

#endif // CHART_DELEGATES_HPP
