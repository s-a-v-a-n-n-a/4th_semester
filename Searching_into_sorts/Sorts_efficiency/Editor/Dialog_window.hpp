#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "Window.hpp"
#include "Color_selection.hpp"
// #include "Search_box.hpp"
#include "../GUI/Input_string.hpp"
#include "../GUI/Slider.hpp"

extern const size_t MIN_INPUT_STRING_HEIGHT;
extern const size_t MIN_SLIDER_HEIGHT;

class Dialog : public Window
{
private:
	size_t offset;

public:
	Dialog(const Visual_object::Config &par_base, const char *name = nullptr);
	
	Button *create_sign_button(const char *assignment);

	Slider *create_slider(const char *assignment = nullptr);
	Color_selection_window *create_color_picker(const char *assignment = nullptr);
	Input_string *create_input_string(const char *assignment = nullptr);

	double get_fraction(Slider *slider);
	Color get_color(Color_selection_window *color_picker);
	char *get_text(Input_string *input);

	void add_visual_object(Visual_object *par_object) override;

	void draw(Screen_information *screen) override;
};

Dialog *create_dialog_window(const size_t width, const size_t height, const char *name = nullptr);
void destroy_dialog_window(Dialog *dialog_window);

#endif // DIALOG_WINDOW_H
