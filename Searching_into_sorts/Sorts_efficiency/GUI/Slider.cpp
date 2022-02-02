#include "Slider.hpp"
#include "../Editor/Application.hpp"

const size_t COSMETIC_OFFSET = 10;
const size_t SLIDER_SIZE = 20;

Slider::Slider(const Visual_object::Config &par_base, Button_delegate *par_delegate, const long long par_high_limit, const long long par_low_limit, const bool par_horizontal, const long long current_pos)
: Visual_object(par_base), delegate(par_delegate), high_limit(par_high_limit), low_limit(par_low_limit), horizontal(par_horizontal)
{
	size_t width = get_width();
	size_t height = get_height();

	size_t line_length = 0;
	if (horizontal)
		line_length = width - 2 * height;
	else
		line_length = height - 2 * width;

	// ползунок
	if (horizontal)
	{
		long long position = height + (line_length - 2 * COSMETIC_OFFSET) - (line_length - 2 * COSMETIC_OFFSET)  * current_pos / (par_high_limit - par_low_limit)  + COSMETIC_OFFSET;
		position = position < (line_length + height/2 - COSMETIC_OFFSET) ? position : (line_length + height/2 - COSMETIC_OFFSET); 
		slider = create_sliding_button(get_position() + Vector_ll(position, 0), height, height, get_position() + Vector_ll(height + COSMETIC_OFFSET, 0), get_position() + Vector_ll(line_length + height/2 - COSMETIC_OFFSET, 0), this);
		current_relation = slider->get_x_relation();
	}
	else
	{
		slider = create_sliding_button(get_position() + Vector_ll(0, width + (line_length - 2 * COSMETIC_OFFSET) - (line_length - 2 * COSMETIC_OFFSET)  * current_pos / (par_high_limit - par_low_limit) + COSMETIC_OFFSET), width, width, get_position() + Vector_ll(0, width + COSMETIC_OFFSET), get_position() + Vector_ll(0, line_length + width - COSMETIC_OFFSET - width/2), this);
		current_relation = slider->get_y_relation();
	}

	// кнопка влево
	// magic !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Button *left = NULL;
	if (horizontal)
		left = create_control_button(get_position(), height, height, SLIDER_LEFT, SLIDER_LEFT_ACTIVE, -1 * (line_length / 10), true, slider);
	else
		left = create_control_button(get_position(), width, width, SLIDER_DOWN, SLIDER_DOWN, -1 * (line_length / 10), false, slider);
	
	// кнопка вправо
	// magic !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Button *right = NULL;
	if (horizontal)
		right = create_control_button(get_position() + Vector_ll(width - height, 0), height, height, SLIDER_RIGHT, SLIDER_RIGHT_ACTIVE, (line_length / 10), true, slider);
	else
		right = create_control_button(get_position() + Vector_ll(height - width, 0), width, width, SLIDER_UP, SLIDER_UP, (line_length / 10), false, slider);
	
	// полосочка, по которой ездят
	// а кто он и что он будет уметь? Светиться? Фон рисовать?
	Magnet_control *line_delegate = new Magnet_control(slider);
	Button *line = nullptr;
	if (horizontal)
	{
		Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(SLIDER_LINE_HOR, line_length, height);
		line = new Button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(height, 0), texture, TRANSPARENT, line_length, height}, line_delegate, "");
	}
	else
	{
		Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(SLIDER_LINE_VER, line_length, height);
		line = new Button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(height, 0), texture, TRANSPARENT, line_length, height}, line_delegate, "");
	}
	add_visual_object(line);

	move_to_end(slider, 0);
}

Magnetic *Slider::create_sliding_button(const Vector_ll &position, const size_t width, const size_t height, const Vector_ll &left_bound, const Vector_ll &right_bound, Visual_object *parent)
{
	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(SLIDER, width, height);
	Magnetic *magnet = new Magnetic({this, (size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, parent, left_bound, right_bound, height); // add delegate
	
	add_visual_object(magnet);

	return magnet;
}

Button *Slider::create_control_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *animating_texture, const long long delta, const bool x_coord, Visual_object *to_control)
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(texture_name, width, height, animating_texture, nullptr);

	// Change_fixedly *change = new Change_fixedly(to_control, delta, x_coord);
	Button *control = new Button({this, (size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, NULL, "");
	Animating_change_fixedly *change = new Animating_change_fixedly(to_control, delta, x_coord, control);
	control->set_delegate(change);

	add_visual_object(control);

	return control;
}

void Slider::count_intermediate_state() const
{
	size_t new_point = (size_t)(current_relation * (double)((double)high_limit - (double)low_limit) + (double)low_limit);

	if (horizontal)
	{
		if (delegate)
			delegate->on_mouse_click(new_point, 0);
	}
	else
		if (delegate)
			delegate->on_mouse_click(0, new_point);
}

void Slider::check_slider_state()
{
	if (horizontal)
	{
		double x_relation = slider->get_x_relation();
		if (x_relation != current_relation)
		{
			current_relation = x_relation;
		}
	}
	else
	{
		double y_relation = slider->get_y_relation();
		if (y_relation != current_relation)
		{
			current_relation = y_relation;
		}
	}
	count_intermediate_state();
}

bool Slider::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	bool result = Visual_object::on_mouse_click(state, par_x, par_y);

	if (result)
	{
		check_slider_state();
	}
	// else
	// {
	// 	result = slider->on_mouse_click(state, par_x, par_y);
	// 	if (result)
	// 		check_slider_state();
	// }

	return result;
}

bool Slider::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool result = Visual_object::on_mouse_move(from, to);

	if (result)
	{
		check_slider_state();
	}
	// else
	// {
	// 	result = slider->on_mouse_move(from, to);
	// 	if (result)
	// 		check_slider_state();
	// }

	return result;
}

void Slider::set_relation(const double relation)
{
	if (horizontal)
		slider->set_x_relation(relation);
	else
		slider->set_y_relation(relation);
}

