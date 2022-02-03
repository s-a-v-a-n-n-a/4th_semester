#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_delegate.hpp"
#include "../GUI/Button.hpp"

class Button_manager : public Visual_object
{
private:
	Vector_ll current_end_position;

	bool x;

public:
	Button_manager(const Visual_object::Config &par_base, bool par_x = true);
	~Button_manager();

	void set_position(const Vector_ll &par_position) override { current_end_position += (par_position - get_position()); Visual_object::set_position(par_position); }

	Button *add_button_x(Button_delegate *par_delegate, const char *par_text, const bool centered, Texture *par_texture, const Color par_color, const size_t par_width, const size_t par_height);
	Button *add_button_y(Button_delegate *par_delegate, const char *par_text, const bool centered, Texture *par_texture, const Color par_color, const size_t par_width, const size_t par_height);
	// Button *add_button(Button_delegate *par_delegate, const char *par_text, const Color par_color, const size_t par_width, const size_t par_height = DEFAULT_BUTTON_HEIGHT);
	Button *add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture, const Color par_color, const size_t par_width = 0, const size_t par_height = 0, const bool centered = true);

	// void draw(Screen_information *screen) override;
};

#endif // BUTTON_MANAGER_H
