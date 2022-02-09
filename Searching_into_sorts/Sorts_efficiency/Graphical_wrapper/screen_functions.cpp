#include "screen_functions.hpp"
#include "../Editor/Application.hpp"

const char *screen_state_text[]
{
    "EVERYTHING IS OKAY\n",
    "LIST DOES NOT EXIST\n",
    "NO MEMORY FOR CONSTRUCTION\n",
    "SEGMENTATION FAULT\n"
};

Screen_information::Screen_information(size_t par_width, size_t par_height) 
: mouse_position(0.0, 0.0), window(sf::VideoMode(par_width, par_height), "It works"), event()//, textures()
{
	width  = par_width;
	height = par_height;

	data = new Color[width * height];
	
	if (data == NULL)
		return;

	mouse_clicked = false;

	font = new sf::Font();
	if (!font->loadFromFile("graphical_attributes/Fonts/OpenGostTypeA-Regular.ttf"))
	{
	    printf("No fonts found\n");
	}

	window.setFramerateLimit(60);
}

Screen_information::~Screen_information()
{
	delete [] data;
	delete font;
}

screen_code Screen_information::set_color(size_t line, size_t column, Color color)
{
	if (line > height || column > width)
		return SCREEN_SEGMENT_FAULT;

	data[line * width + column] = color;

	return SCREEN_OK;
}

size_t Screen_information::get_width()
{
	return width;
}

size_t Screen_information::get_height()
{
	return height;
}

// sf::BlendMode blending_mode(const Blend_mode mode)
// {
// 	switch (mode)
// 	{
// 	case Blend_mode::ALPHA:
// 		return sf::BlendAlpha;
	
// 	case Blend_mode::ADD:
// 		return sf::BlendAdd;

// 	case Blend_mode::MULTIPLY:
// 		return sf::BlendMultiply;

// 	case Blend_mode::COPY:
// 		return sf::BlendNone;

// 	default:
// 		return sf::BlendAlpha;
// 	}
// }

// draw_to_pixels(Color *pixels, const size_t width, const size_t height, sf::Shape *shape)
// {
// 	sf::Texture texture;
// 	texture.create(width, height);

// 	texture_load(&texture, pixels, width, height);

// 	sf::Sprite sprite;
// 	sprite.setTexture(texture);

// 	sf::RenderTexture render;
// 	render.create(width, height);
// 	render.clear(TRANSPARENT);

// 	render.draw(sprite);
// 	render.draw(*shape);

// 	render.display();
// }

void Screen_information::draw_circle(const Vector_ll &par_position, const double par_radius, const Color &par_color, const Color &par_fill_color, const Blend_mode mode)//, Color *pixels, const Vector_ll params)
{
	// printf("I was asked to draw circle: of size %lg, of Color %u %u %u %u, at position %lld %lld, mode %d\n", par_radius, par_color.r, par_color.g, par_color.b, par_color.a, par_position.get_x(), par_position.get_y(), (int)mode);

	// sf::CircleShape circle(par_radius);

	// circle.setPosition(sf::Vector2f(par_position.get_x(), par_position.get_y()));

	// sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	// sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	// circle.setOutlineColor(color);
	// circle.setFillColor(fill_color);

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(circle, blend);
	Renderer::Object obj = { &window, par_position, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_circle({0, 0}, par_radius, par_color, par_fill_color);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::draw_rectangle(const Vector_ll &par_position, const double par_width, const double par_height, const Color &par_color, const Color &par_fill_color, const Blend_mode mode)//, Color *pixels, const Vector_ll params)
{
	// sf::RectangleShape rectangle(sf::Vector2f(par_width, par_height));

	// rectangle.setPosition(sf::Vector2f(par_position.get_x(), par_position.get_y()));

	// sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	// rectangle.setOutlineColor(color);

	// sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	// rectangle.setFillColor(fill_color);

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(rectangle, blend);
	Renderer::Object obj = { &window, par_position, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_rectangle({0, 0}, par_width, par_height, par_color, par_fill_color);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::draw_triangle(const Vector_ll &point1, const Vector_ll &point2, const Vector_ll &point3, const Color &par_color, const Color &par_fill_color, const Blend_mode mode)//, Color *pixels, const Vector_ll params)
{
	// sf::ConvexShape convex;

	// convex.setPointCount(3);
	
	// convex.setPoint(0, sf::Vector2f(point1.get_x(), point1.get_y()));
	// convex.setPoint(1, sf::Vector2f(point2.get_x(), point2.get_y()));
	// convex.setPoint(2, sf::Vector2f(point3.get_x(), point3.get_y()));

	// sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	// convex.setOutlineColor(color);

	// sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	// convex.setFillColor(fill_color);

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(convex, blend);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_triangle(point1, point2, point3, par_color, par_fill_color);
	Application::get_app()->get_renderer()->pop_back();
}


void Screen_information::draw_point(const Vector_ll &par_point, const Color &par_color, const Blend_mode mode)//, Color *pixels, const Vector_ll params)
{
	// sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	// sf::Vertex sfml_point(sf::Vector2f(par_point.get_x(), par_point.get_y()), color);

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(&sfml_point, 1, sf::Points, blend);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_point(par_point, par_color);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::draw_line(const Vector_ll &left, const Vector_ll &right, const Color &par_color, const Blend_mode mode)//, Color *pixels, const Vector_ll params)
{
	// sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	// sf::Vertex sfml_line[] = {  sf::Vertex(sf::Vector2f(left.get_x(), left.get_y()), color), 
	// 							sf::Vertex(sf::Vector2f(right.get_x(), right.get_y()), color) };
	
	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(sfml_line, 2, sf::Lines, blend);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_line(left, right, par_color);
	Application::get_app()->get_renderer()->pop_back();
}


void Screen_information::draw_text(const char *par_text, const Vector_ll &par_position, const Color &par_color, const size_t par_text_size, const bool centered)
{
	if (!font)
		return;

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);

	sf::Text drawable_text = {};//(par_text, font, par_text_size);
	drawable_text.setFont(*font);
	drawable_text.setString(par_text);
	drawable_text.setCharacterSize(par_text_size);
	drawable_text.setFillColor(color);
	
	int x = par_position.get_x();
	int y = par_position.get_y();

	if (centered)
	{
		x -= drawable_text.getGlobalBounds().width / 2;
	}
	y -= drawable_text.getGlobalBounds().height;
	// else
	// {
	// 	x -= drawable_text.getGlobalBounds().width;
	// 	y -= drawable_text.getGlobalBounds().height;
	// }

	drawable_text.setPosition(x, y);

	window.draw(drawable_text);
}

void Screen_information::draw_image(const Color *array, const Vector_ll &position, const size_t width, const size_t height, const Blend_mode mode)
{
	// sf::Texture texture;
	// texture.create(width, height);

	// texture_load(&texture, array, width, height);

	// draw_texture(position, &texture, width, height, 1, mode);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_image(array, position, width, height);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::draw_texture(const Vector_ll &position, const char *texture_name, const Blend_mode mode)
{
	// sf::Sprite sprite;
	// sf::Texture texture;
	// texture.loadFromFile(texture_name);

	// sprite.setTexture(texture);

	// sprite.setPosition(position.get_x(), position.get_y());

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(sprite, blend);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_texture(position, texture_name);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::draw_texture(const Vector_ll &position, const sf::Texture *texture, const size_t width, const size_t height, const double transperancy, const Blend_mode mode)
{
	// sf::Sprite sprite;

	// // sf::RenderTexture render_texture;
	// // render_texture.create(get_width(), get_height());

	// size_t texture_width = texture->getSize().x;
	// size_t texture_height = texture->getSize().y;

	// sprite.setPosition(position.get_x(), position.get_y());

	// double scale_x = (double)width / (double)texture_width;
	// double scale_y = (double)height / (double)texture_height;

	// // render_texture.draw(texture);
	// // if (scale_x > 1 || scale_y > 1)
	// // {
	// // 	render_texture.setSmooth(true);
	// // }


	// sprite.setTexture(*texture);
	// sprite.setScale(scale_x, scale_y);

	// // double max_color = (double)MAX_COLOR_VALUE;
	// // max_color *= transperancy;
	// // // printf("brightness %lg\n", max_color);
	// // sprite.setColor(sf::Color(255, 255, 255, (unsigned char)max_color));

	// sf::BlendMode blend = blending_mode(mode);
	// window.draw(sprite, blend);
	Renderer::Object obj = { &window, {0, 0}, mode};
	Application::get_app()->get_renderer()->push_back(&obj);
	Application::get_app()->get_renderer()->draw_texture(position, texture, width, height, transperancy);
	Application::get_app()->get_renderer()->pop_back();
}

void Screen_information::reset()
{
	window.clear();
}

void Screen_information::sfml_update_mouse_state()
{
	sfml_update_mouse_position();
	sfml_update_mouse_pressed_state();
}

void Screen_information::sfml_update_mouse_position()
{
	sf::Vector2i sfml_position(mouse.getPosition(window));

	mouse_position = Vector_ll(sfml_position.x, sfml_position.y);
}

void Screen_information::sfml_update_mouse_pressed_state()
{
	mouse_clicked = mouse.isButtonPressed(mouse.Left);
}

void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column)
{
	screen.data[line * screen.width + column].r = color.r;
	screen.data[line * screen.width + column].g = color.g;
	screen.data[line * screen.width + column].b = color.b;
	screen.data[line * screen.width + column].a = color.a;
}

screen_code screen_load(Screen_information &screen, sf::Image *image)
{
	sf::Vector2u image_size = (*image).getSize();
	if (image_size.x < screen.width || image_size.y < screen.height)
		return SCREEN_SEGMENT_FAULT;

	for (size_t i = 0; i < screen.height; i++) {
		for (size_t j = 0; j < screen.width; j++)
		{
			sf::Color color(screen.data[i * screen.width + j].r, screen.data[i * screen.width + j].g,
				            screen.data[i * screen.width + j].b, screen.data[i * screen.width + j].a);

			image->setPixel(j, i, color);
		}
	}

	return SCREEN_OK;
}

void Screen_information::image_load(sf::Image *image, const Color *to_draw, const size_t width, const size_t height)
{
	sf::Vector2u image_size = (*image).getSize();
	if (image_size.x < width || image_size.y < height)
		return;

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++)
		{
			sf::Color color(to_draw[i * width + j].r, to_draw[i * width + j].g,
				            to_draw[i * width + j].b, to_draw[i * width + j].a);

			image->setPixel(j, i, color);
		}
	}
}

// void Screen_information::texture_load(sf::Texture *texture, const Color *to_draw, const size_t width, const size_t height)
// {
// 	sf::Vector2u texture_size = (*texture).getSize();
// 	if (texture_size.x < width || texture_size.y < height)
// 		return;

// 	texture->update((sf::Uint8*)to_draw, width, height, 0, 0);
// }

void draw_shape_sfml(sf::RenderWindow *window, Screen_information &screen)
{
	sf::Sprite sprite;
	sf::Texture texture;
	texture.create(screen.width, screen.height);

	sprite.setTexture(texture);

	sf::Image image;
	image.create(screen.width, screen.height, sf::Color::Black);

	screen_load(screen, &image);

	texture.update(image);

	window->draw(sprite);
}

Vector_ll get_image_size(const char *filename)
{
	sf::Image image;
	image.loadFromFile(filename);

	sf::Vector2u size = image.getSize();
	
	return Vector_ll(size.x, size.y);
}
