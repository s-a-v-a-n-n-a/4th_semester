#ifndef WINDOW_CONTROL_PANEL_VIDGET
#define WINDOW_CONTROL_PANEL_VIDGET

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Button_manager.hpp"
#include "../GUI/Resource_manager.hpp"

#include "Graphical_delegates.hpp"

class Window_control_panel : public Visual_object
{
private:

public:
	Window_control_panel(const Visual_object::Config &par_base, Visual_object *whose, const char *name = nullptr);
	// Window_control_panel(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *whose);
	// Window_control_panel(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Visual_object *whose);
	~Window_control_panel();

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
};

class Closing_window_control_panel : public Visual_object
{
public:
	Closing_window_control_panel(const Visual_object::Config &par_base, Visual_object *whose, const char *name = nullptr);
	~Closing_window_control_panel();
};

#endif // WINDOW_CONTROL_PANEL_VIDGET
