#include "Window.hpp"
#include "Application.hpp"

Window::Window(const Visual_object::Config &par_base, const char *name)
: Visual_object(par_base)
{
	create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT, name);
}

Window_control_panel *Window::create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height, const char *name)
{
	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(WINDOW_HEADER, width, height);
	Visual_object::Config panel_base = { this, (size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
											position, 
											texture, 
											TRANSPARENT,
											width,
											height};

	Window_control_panel *control = new Window_control_panel(panel_base, parent, name);
	add_visual_object(control);

	return control;
}

Closing_window::Closing_window(const Visual_object::Config &par_base, const char *name)
: Visual_object(par_base)
{
	create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT, name);
}

Closing_window_control_panel *Closing_window::create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height, const char *name)
{
	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(WINDOW_HEADER, width, height);
	Visual_object::Config panel_base = { this, (size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
											position, 
											texture, 
											TRANSPARENT,
											width,
											height};

	Closing_window_control_panel *control = new Closing_window_control_panel(panel_base, parent);
	add_visual_object(control);

	return control;
}
