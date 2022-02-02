#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include <SFML/Graphics.hpp>

#include "Visual_object_base.hpp"
#include "Button_delegate.hpp" 
#include "Text.hpp"

const Color DEFAULT_TEXT_COLOR = BLACK;
extern const size_t DEFAULT_BUTTON_HEIGHT;
extern const size_t DEFAULT_BUTTON_WIDTH;
extern const size_t INCREASED_BUTTON_HEIGHT;

class Button : public Visual_object
{
private:
	Button_delegate *click;

	bool pressed;

public:
	Button() = delete;
	Button(const Visual_object::Config &base, Button_delegate *par_click);
	Button(const Visual_object::Config &base, Button_delegate *par_click, const char *par_text, const bool centered = true);
	// Button(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Button_delegate *par_click, const char *par_text);
	// Button(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Button_delegate *par_click, const char *par_text);
	~Button();

	void set_delegate(Button_delegate *par_click) { click = par_click; }

	void draw(Screen_information *screen) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void tick(const double delta) override { ; }

	bool get_pressed() { return pressed; }
	void set_pressed(const bool par_pressed) { pressed = par_pressed; }
};

class Magnetic : public Visual_object
{
private:
	Visual_object *parent;
	Vector_ll last_parent_position;

	Button_delegate *delegate;

	Vector_ll left_bound;
	Vector_ll right_bound;

	double x_relation;
	double y_relation;

	size_t radius;

	bool pressed;

public:
	Magnetic() = delete;
	Magnetic(const Visual_object::Config &par_base, Visual_object *par_parent, const Vector_ll &par_left_bound, const Vector_ll &par_right_bound, const size_t par_radius = 0, Button_delegate *par_delegate = NULL);
	~Magnetic();

	void set_position(const Vector_ll &par_position) override;

	bool in_x_bounds(const size_t par_x, const size_t par_y);
	bool in_y_bounds(const size_t par_x, const size_t par_y);

	double get_x_relation() const { return x_relation; }
	double get_y_relation() const { return y_relation; }
	
	void set_x_relation(const double par_x_relation);
	void set_y_relation(const double par_y_relation);

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	bool get_pressed() { return pressed; }
	void set_pressed(const bool par_pressed) { pressed = par_pressed; }
	// void set_relative_position(const Vector_ll &par_relative_position) { relative_position = par_relative_position; }
};

#endif // BUTTON_CLASS
