#ifndef WINDOW_H
#define WINDOW_H

#include "../GUI/Visual_object_base.hpp"
// #include "../GUI/Resource_manager.hpp"

#include "Window_control_panel.hpp"

class Window : public Visual_object
{
private:

public:
	Window(const Visual_object::Config &par_base, const char *name = nullptr);

	Window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height, const char *name = nullptr);
};

class Closing_window : public Visual_object
{
private:

public:
	Closing_window(const Visual_object::Config &par_base, const char *name = nullptr);

	Closing_window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height, const char *name = nullptr);
};

#endif // WINDOW_H
