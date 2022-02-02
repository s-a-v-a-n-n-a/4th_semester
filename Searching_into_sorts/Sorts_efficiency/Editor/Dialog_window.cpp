#include "Dialog_window.hpp"

#include "Application.hpp"

const size_t MIN_INPUT_STRING_HEIGHT = 50;
const size_t MIN_SLIDER_HEIGHT = 30;

Dialog *create_dialog_window(const size_t width, const size_t height, const char *name)
{
	Visual_object *editor = Application::get_app()->get_default();

	Vector_ll main_position = editor->get_position();
	Vector_ll main_window_size = Vector_ll(editor->get_width(), editor->get_height());
	Vector_ll dialog_size = Vector_ll(width, height);

	if (dialog_size.get_x() > main_window_size.get_x())
		dialog_size.set_x(main_window_size.get_x() - 10);
	if (dialog_size.get_y() > main_window_size.get_y())
		dialog_size.set_y(main_window_size.get_y() - 10);
	
	size_t x_pos = main_position.get_x() + rand() % (main_window_size.get_x() - dialog_size.get_x());  
	size_t y_pos = main_position.get_y() + rand() % (main_window_size.get_y() - dialog_size.get_y());  

	Vector_ll position = Vector_ll(x_pos, y_pos);

	Full_texture *background = Application::get_app()->get_rescrs()->create_texture(WINDOW_BACKGROUND, (size_t)dialog_size.get_x(), (size_t)dialog_size.get_y());// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	Dialog *dialog_window = new Dialog({editor, (size_t)Vidget_type::DIALOG, position, background, TRANSPARENT, (size_t)dialog_size.get_x(), (size_t)dialog_size.get_y()}, name);
	editor->add_visual_object(dialog_window);

	return dialog_window;
}

void destroy_dialog_window(Dialog *dialog_window)
{
	Visual_object *editor = Application::get_app()->get_default();

	editor->very_slow_delete_visual_object(dialog_window);
}

Dialog::Dialog(const Visual_object::Config &par_base, const char *name)
: Window(par_base, name), offset(DEFAULT_BUTTON_HEIGHT) // DEFAULT_BUTTON_HEIGHT
{
	;
}

Button *Dialog::create_sign_button(const char *assignment)
{
	Button *sign = new Button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, offset), nullptr, TRANSPARENT, get_width(), DEFAULT_BUTTON_HEIGHT}, nullptr, assignment, false);
	add_visual_object(sign);

	offset += DEFAULT_BUTTON_HEIGHT;

	return sign;
}

Slider *Dialog::create_slider(const char *assignment)
{
	if (assignment)
	{
		create_sign_button(assignment);
	}

	long long height = MIN_SLIDER_HEIGHT < (get_height() - offset) ? MIN_SLIDER_HEIGHT : get_height() - offset; 
	if (height <= 0)
	{
		set_height(get_height() + MIN_SLIDER_HEIGHT);
		height = MIN_SLIDER_HEIGHT;
	}
	Slider *slider = new Slider({this, (size_t)Vidget_type::SLIDER, get_position() + Vector_ll(0, offset), NULL, TRANSPARENT, get_width(), (size_t)height}, NULL, 0, 1, true);

	offset += height;

	add_visual_object(slider);

	return slider;
}

Color_selection_window *Dialog::create_color_picker(const char *assignment)
{
	size_t width = get_width();
	if (assignment)
	{
		create_sign_button(assignment);
	}

	long long height = width < (get_height() - offset) ? width : get_height() - offset; 
	if (height <= 0)
	{
		set_height(get_height() + width);
		height = width;
	}
	Visual_object::Config picker_base = { this, (size_t)Vidget_type::COLOR_SELECTION, get_position() + Vector_ll(0, offset), NULL, TRANSPARENT, width, (size_t)height};

	Color_selection_window *picker = new Color_selection_window(picker_base, RED);

	offset += height;

	add_visual_object(picker);

	return picker;
}

Input_string *Dialog::create_input_string(const char *assignment)
{
	if (assignment)
	{
		create_sign_button(assignment);
	}

	long long height = MIN_INPUT_STRING_HEIGHT < (get_height() - offset) ? MIN_INPUT_STRING_HEIGHT : get_height() - offset; 
	if (height <= 0)
	{
		set_height(get_height() + MIN_INPUT_STRING_HEIGHT);
		height = MIN_INPUT_STRING_HEIGHT;
	}

	Animating_texture *text_field_texture = Application::get_app()->get_rescrs()->create_texture(TEXT_FIELD, get_width(), (size_t)height, TEXT_FIELD_ACTIVE, NULL);
	Input_string *input = new Input_string({this, (size_t)Vidget_type::INPUT_STRING, get_position() + Vector_ll(0, offset), text_field_texture, TRANSPARENT, get_width(), (size_t)height});
	
	offset += height;

	add_visual_object(input);

	return input;
}

double Dialog::get_fraction(Slider *slider)
{
	return 1 - slider->get_relation();
}

Color Dialog::get_color(Color_selection_window *color_picker)
{
	return color_picker->get_color();
}

char *Dialog::get_text(Input_string *input)
{
	return input->get_message();
}

void Dialog::add_visual_object(Visual_object *par_object)
{
	get_objects()->add_to_end(par_object); 
	// par_object->set_position(par_object->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT));
}

void Dialog::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	// printf("I AM PRESENT AAAAAAAAAAAAAA\n");
}

