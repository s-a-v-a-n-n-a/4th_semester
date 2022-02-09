#ifndef MAIN_PAGE_HPP
#define MAIN_PAGE_HPP

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Resource_manager.hpp"

#include "../math_structures/Sorts.hpp"

#include "Bar_graph.hpp"
#include "Vidget_types.hpp"
#include "Int_array_delegates.hpp"

extern const char *BUTTON_CHART_TEXTS[];

class Main_page : public Visual_object
{
private:

public:
	Main_page(const Visual_object::Config &par_base);
	virtual ~Main_page();

	bool on_key_pressed(const bool pressed_state, const unsigned key_state) override;

	Bar_graph *create_bar_graph(const Vector_ll &position, const Vector_ll &size, const Color &color, Int_container *array);
	Button *create_sort_button(const Vector_ll &position, const Vector_ll &size, const char *name, const Color &color, size_t colored_texture_index, Int_container *array, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)));
	Button *create_shuffle_button(const Vector_ll &position, const Vector_ll &size, const Color &color, Intercepted_int *array, size_t arr_len);
	Button *create_refill_button(const Vector_ll &position, const Vector_ll &size, const char *name, const size_t colored_texture_number, Bar_graph *graph, Int_container *array);
	// Chart_window *create_chart_window(const Vector_ll &position, const Vector_ll &size, const Color &color, const char *name);
	// Button *create_control_button(Chart_window *chart_ass, Chart_window *chart_cmp, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)));
	// Button *create_clear_button(std::vector<Chart_window*> charts, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color);

	void add_visual_object(Visual_object *par_object) override;
};


#endif // MAIN_PAGE_HPP
