#include "Button_manager.hpp"

Button_manager::Button_manager(const Visual_object::Config &par_base, bool par_x)
: Visual_object(par_base), current_end_position(par_base.position), x(par_x)
{
    // size_t button_height = par_height;

    // size_t current_button_offset = 0;

    current_end_position = get_position();
}

// Button_manager::Button_manager(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height)
// : Visual_object(par_type, par_position, par_color, par_width, par_height)
// {
//     size_t button_height = par_height;

//     size_t current_button_offset = 0;

//     current_end_position = par_position;
// }

Button_manager::~Button_manager()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

// Button *Button_manager::add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture, const size_t par_width, const size_t par_height)

Button *Button_manager::add_button_x(Button_delegate *par_delegate, const char *par_text, const bool centered, Texture *par_texture, const Color par_color, const size_t par_width, const size_t par_height)
{
	size_t button_width = par_width == 0 ? (par_texture? par_texture->get_width() : DEFAULT_BUTTON_WIDTH) : par_width;
	size_t button_height = get_height();

	if (current_end_position.get_x() + par_width > get_position().get_x() + get_width())
		set_width(current_end_position.get_x() - get_position().get_x() + par_width);

	Visual_object::Config buttton_base = { this, (size_t)Vidget_type::BUTTON,
    										current_end_position, 
    										par_texture,
    										par_color, 
								  			button_width, 
								  			button_height };

	Button *new_button = new Button(buttton_base,
								  	par_delegate, 
								  	par_text,
								  	centered);

	current_end_position += Vector_ll(button_width, 0);
	
	add_visual_object(new_button);

	return new_button;
}

Button *Button_manager::add_button_y(Button_delegate *par_delegate, const char *par_text, const bool centered, Texture *par_texture, const Color par_color, const size_t par_width, const size_t par_height)
{
	size_t button_width = get_width();
	size_t button_height = ((par_height == 0) ? (par_texture ? par_texture->get_height() : DEFAULT_BUTTON_HEIGHT) : par_height);

	if (current_end_position.get_y() + button_height > get_position().get_y() + get_height())
		set_height(current_end_position.get_y() - get_position().get_y() + button_height);

	Visual_object::Config button_base = { this, (size_t)Vidget_type::BUTTON,
    										current_end_position, 
    										par_texture,
    										par_color, 
								  			button_width, 
								  			button_height };

	Button *new_button = new Button(button_base,
								  	par_delegate, 
								  	par_text,
								  	centered);
	
	current_end_position += Vector_ll(0, button_height);

	add_visual_object(new_button);
	
	return new_button;
}

Button *Button_manager::add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture, const Color par_color, const size_t par_width, const size_t par_height, const bool centered)
{
	if (x)
		return add_button_x(par_delegate, par_text, centered, par_texture, par_color, par_width, par_height);
	else
		return add_button_y(par_delegate, par_text, centered, par_texture, par_color, par_width, par_height);
}

// void Button_manager::draw(Screen_information *screen)
// {
// 	Visual_object **objects_array = get_objects()->get_array();
// 	size_t objects_amount = get_objects()->get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		if (objects_array[i]->get_visible())
// 		{
// 			objects_array[i]->draw(screen);
// 		}
// 	}	
// }
