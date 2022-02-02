#include "Window_control_panel.hpp"
#include "Application.hpp"

Window_control_panel::Window_control_panel(const Visual_object::Config &par_base, Visual_object *whose, const char *name)
: Visual_object(par_base)
{
	Visual_object::Config panel_base = { this, (size_t)Vidget_type::BUTTON_MANAGER, get_position(), nullptr, TRANSPARENT, get_width(), DEFAULT_BUTTON_HEIGHT };
	Button_manager *panel = new Button_manager(panel_base);

	// Full_texture *roll_up_texture = new Full_texture(ROLL_UP_TEXTURE);
	Animating_texture *close_texture = Application::get_app()->get_rescrs()->create_texture(CLOSE_TEXTURE, get_height(), get_height(), CLOSE_MOVE_TEXTURE, nullptr);
	// close_texture->set_move_texture(CLOSE_MOVE_TEXTURE);

	Drag_and_drop_delegate *drag_and_drop = new Drag_and_drop_delegate(whose);


	if (name)
		panel->add_button(drag_and_drop, name, nullptr, TRANSPARENT, get_width() - get_height(), get_height(), false); //  - roll_up_texture->get_width() 
	else
		panel->add_button(drag_and_drop, "", nullptr, TRANSPARENT, get_width() - get_height(), get_height(), false); //  - roll_up_texture->get_width() 

	// Roll_up_delegate *rolling_up = new Roll_up_delegate(whose);
	Button *roll = panel->add_button(nullptr, "", close_texture, TRANSPARENT, get_height(), get_height());
	Roll_up_delegate *rolling_up = new Roll_up_delegate(roll);
	if (roll)
		roll->set_delegate(rolling_up);
	else
		delete rolling_up;
	// panel->add_button(rolling_up, "", roll_up_texture);
	    
	// Close_delegate *closing = new Close_delegate(whose);
	

	add_visual_object(panel);

	// set_active(close);
}

Window_control_panel::~Window_control_panel()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}


Closing_window_control_panel::Closing_window_control_panel(const Visual_object::Config &par_base, Visual_object *whose, const char *name)
: Visual_object(par_base)
{
	Visual_object::Config panel_base = { this, (size_t)Vidget_type::BUTTON_MANAGER, get_position(), nullptr, TRANSPARENT, get_width(), DEFAULT_BUTTON_HEIGHT };
	Button_manager *panel = new Button_manager(panel_base);

	Animating_texture *close_texture = Application::get_app()->get_rescrs()->create_texture(CLOSE_TEXTURE, get_height(), get_height(), CLOSE_MOVE_TEXTURE, nullptr);
	
	Drag_and_drop_delegate *drag_and_drop = new Drag_and_drop_delegate(whose);

	if (name)
		panel->add_button(drag_and_drop, name, nullptr, TRANSPARENT, get_width() - get_height(), get_height(), false); //  - roll_up_texture->get_width() 
	else
		panel->add_button(drag_and_drop, "", nullptr, TRANSPARENT, get_width() - get_height(), get_height(), false); //  - roll_up_texture->get_width() 

	Button *close = panel->add_button(nullptr, "", close_texture, TRANSPARENT, get_height(), get_height());
	Close_delegate *closing = new Close_delegate(close);
	if (close)
		close->set_delegate(closing);
	else
		delete closing;
	

	add_visual_object(panel);
}

Closing_window_control_panel::~Closing_window_control_panel()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}
