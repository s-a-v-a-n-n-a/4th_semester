#ifndef SLIDER_H
#define SLIDER_H

#include "../Editor/Graphical_delegates.hpp"

#include "Resource_manager.hpp"
#include "Visual_object_base.hpp"
#include "Button.hpp"

extern const size_t COSMETIC_OFFSET;
extern const size_t SLIDER_SIZE;

class Slider : public Visual_object
{
protected:
	Button_delegate *delegate;
	Magnetic *slider;

	double current_relation;

	long long high_limit;
	long long low_limit;

	bool horizontal = true;

public:
	Slider(const Visual_object::Config &par_base, Button_delegate *par_delegate, const long long par_high_limit, const long long par_low_limit, const bool par_horizontal, const long long current_pos = 0);

	Button *create_control_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *animating_texture, const long long delta, const bool x_coord, Visual_object *to_control);
	Magnetic *create_sliding_button(const Vector_ll &position, const size_t width, const size_t height, const Vector_ll &left_bound, const Vector_ll &right_bound, Visual_object *parent);

	void count_intermediate_state() const;
	void check_slider_state();

	Magnetic *get_slider() { return slider; }

	bool get_horizontal() const { return horizontal; }

	double get_relation() { return current_relation; }
	void set_relation(const double relation);

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// Ползунок:
// 1) кнопки перемещают ползунок И вызвают делегата
// 2) перемещаясь, ползунок вызывает своего делегата
// 
// Хочу второй. ползунком будет magnetic
// 

#endif // SLIDER_H
