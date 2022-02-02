#ifndef MAIN_PAGE_HPP
#define MAIN_PAGE_HPP

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../GUI/Resource_manager.hpp"

#include "../math_structures/Sorts.hpp"

#include "Chart_window.hpp"
#include "Vidget_types.hpp"

class Main_page : public Visual_object
{
private:

public:
	Main_page(const Visual_object::Config &par_base);
	virtual ~Main_page();

	bool on_key_pressed(const bool pressed_state, const unsigned key_state) override;

	Chart_window *create_chart_window(const Vector_ll &position, const Vector_ll &size, const Color &color);
	Button *create_control_button(Chart_window *chart, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)));

	void add_visual_object(Visual_object *par_object) override;
};


#endif // MAIN_PAGE_HPP
