#ifndef SCREEN_INFORMATION
#define SCREEN_INFORMATION

#include <SFML/Graphics.hpp>
#include <cstring>
#include <cstdio>

#include "Renderer.hpp"
#include "Texture_names.hpp"

#include "Event_handler.hpp"
#include "Texture.hpp"
#include "Text.hpp"

#include "../math_structures/Radius_vector.hpp"

#include "../simple_list/simple_list.hpp"

// #define Vector_ll Vector_ll<unsigned>

typedef enum Screen_information_code_errors 
{ 
	SCREEN_OK,
    SCREEN_NULL,
    SCREEN_NO_CONSTRUCT,
    SCREEN_SEGMENT_FAULT
} screen_code;

// enum class Blend_mode
// {
// 	ALPHA, 
// 	ADD, 
// 	MULTIPLY,
// 	COPY
// };

// sf::BlendMode blending_mode(const Blend_mode mode);

extern const char *screen_state_text[];

class Screen_information 
{
private:
	// Renderer renderer;

	Vector_ll mouse_position;
	bool mouse_clicked;

	Color *data;
	size_t width;
	size_t height;

public:
	Event_handler event_handler; 

	sf::RenderWindow window;
	sf::Event event; 
	sf::Mouse mouse;

	sf::Font *font;

	// Texture_manager textures;

	Screen_information(size_t par_width, size_t par_height);
	~Screen_information();

	screen_code set_color(size_t line, size_t column, Color color);
	
	// getters
	// ---------------------------------------------------------------------
	size_t get_width();
	size_t get_height();
	bool      get_mouse_pressed_state() { return mouse_clicked; }
	Vector_ll get_mouse_position() const { return mouse_position; }
	// ---------------------------------------------------------------------

	// setters 
	// ---------------------------------------------------------------------
	void set_mouse_state(const bool par_state) { mouse_clicked = par_state; }
	// ---------------------------------------------------------------------
	
	// sf::BlendMode blending_mode(const Blend_mode mode);

	// drawings
	// ---------------------------------------------------------------------
	void draw_circle(const Vector_ll &par_position, const double par_radius, const Color &par_color, const Color &par_fill_color = TRANSPARENT, const Blend_mode mode = Blend_mode::ALPHA);//, Color *pixels = nullptr, const Vector_ll params = {0, 0});
	void draw_rectangle(const Vector_ll &par_position, const double par_width, const double par_height, const Color &par_color, const Color &par_fill_color = TRANSPARENT, const Blend_mode mode = Blend_mode::ALPHA);//, Color *pixels = nullptr, const Vector_ll params = {0, 0});
	void draw_triangle(const Vector_ll &point1, const Vector_ll &point2, const Vector_ll &point3, const Color &par_color, const Color &par_fill_color = TRANSPARENT, const Blend_mode mode = Blend_mode::ALPHA);//, Color *pixels = nullptr, const Vector_ll params = {0, 0});
	void draw_point(const Vector_ll &point, const Color &par_color, const Blend_mode mode = Blend_mode::ALPHA);//, Color *pixels = nullptr, const Vector_ll params = {0, 0});
	void draw_line(const Vector_ll &left, const Vector_ll &right, const Color &par_color, const Blend_mode mode = Blend_mode::ALPHA);//, Color *pixels = nullptr, const Vector_ll params = {0, 0});
	void draw_text(const char *par_text, const Vector_ll &par_position, const Color &par_color, const size_t text_size, const bool centered = true);
	void draw_image(const Color *array, const Vector_ll &position, const size_t width, const size_t height, const Blend_mode mode = Blend_mode::ALPHA);
	void draw_texture(const Vector_ll &position, const char *texture_name, const Blend_mode mode = Blend_mode::ALPHA);
	void draw_texture(const Vector_ll &position, const sf::Texture *texture, const size_t width, const size_t height, const double transperancy = 1.0, const Blend_mode mode = Blend_mode::ALPHA);
	// ---------------------------------------------------------------------
	
	void reset();

	void sfml_update_mouse_state();
	void sfml_update_mouse_position();
	void sfml_update_mouse_pressed_state();

	void image_load(sf::Image *image, const Color *to_draw, const size_t width, const size_t height);
	// void texture_load(sf::Texture *texture, const Color *to_draw, const size_t width, const size_t height);

	friend void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column);
	friend screen_code screen_load(Screen_information &screen, sf::Image* image);
	friend void draw_shape_sfml(sf::RenderWindow *window, Screen_information &screen);
};

Vector_ll get_image_size(const char *filename);

#endif // SCREEN_INFORMATION
