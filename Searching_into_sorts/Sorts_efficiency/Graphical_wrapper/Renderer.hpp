#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <cstring>
#include <cstdio>

#include "colors.hpp"

#include "../math_structures/Radius_vector.hpp"
#include "../simple_list/simple_list.hpp"

enum class Blend_mode
{
	ALPHA, 
	ADD, 
	MULTIPLY,
	COPY
};

sf::BlendMode blending_mode(const Blend_mode mode);
void texture_load(sf::Texture *texture, const Color *to_draw, const size_t width, const size_t height);

class Renderer
{
public:
	struct Object
	{
		sf::RenderTarget *render;

		Vector_ll offset;
		Blend_mode mode;
	};

	Renderer();
	~Renderer() = default;

	void push_back(Renderer::Object *obj);
	Renderer::Object *pop_back();
	Renderer::Object *get_last();

	void draw_circle(const Vector_ll &par_position, const double par_radius, const Color &par_color, const Color &par_fill_color = TRANSPARENT);
	void draw_rectangle(const Vector_ll &par_position, const double par_width, const double par_height, const Color &par_color, const Color &par_fill_color = TRANSPARENT);
	void draw_triangle(const Vector_ll &point1, const Vector_ll &point2, const Vector_ll &point3, const Color &par_color, const Color &par_fill_color = TRANSPARENT);
	void draw_point(const Vector_ll &point, const Color &par_color);
	void draw_line(const Vector_ll &left, const Vector_ll &right, const Color &par_color);
	// void draw_text(const char *par_text, const Vector_ll &par_position, const Color &par_color, const size_t text_size, const bool centered = true);
	void draw_image(const Color *array, const Vector_ll &position, const size_t width, const size_t height);
	
	void draw_texture(const Vector_ll &position, const char *texture_name);
	void draw_texture(const Vector_ll &position, const sf::Texture *texture, const size_t width, const size_t height, const double transperancy = 1.0);
	void draw_texture(const Vector_ll &position, const sf::RenderTexture *texture, const size_t width, const size_t height, const double transperancy = 1.0);

	void clear_texture(sf::RenderTexture *texture, const Color &color = TRANSPARENT);
	Color *texture2data(sf::RenderTexture *texture, const size_t width, const size_t height);
	void data2texture(sf::RenderTexture *texture, Color *data, const size_t width, const size_t height);
private:
	List<Renderer::Object*> stack;
};

#endif // RENDERER_HPP
