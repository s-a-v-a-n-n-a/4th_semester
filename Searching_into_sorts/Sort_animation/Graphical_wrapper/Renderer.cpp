#include "Renderer.hpp"

sf::BlendMode blending_mode(const Blend_mode mode)
{
	switch (mode)
	{
	case Blend_mode::ALPHA:
		return sf::BlendAlpha;
	
	case Blend_mode::ADD:
		return sf::BlendAdd;

	case Blend_mode::MULTIPLY:
		return sf::BlendMultiply;

	case Blend_mode::COPY:
		return sf::BlendNone;

	default:
		return sf::BlendAlpha;
	}
}

void texture_load(sf::Texture *texture, const Color *to_draw, const size_t width, const size_t height)
{
	sf::Vector2u texture_size = (*texture).getSize();
	if (texture_size.x < width || texture_size.y < height)
		return;

	texture->update((sf::Uint8*)to_draw, width, height, 0, 0);
}

Renderer::Renderer() : stack() {}

void Renderer::push_back(Renderer::Object *obj)
{
	stack.add_to_end(obj);
}

Renderer::Object *Renderer::pop_back()
{
	size_t last_obj_idx = stack.get_length() - 1;
	Renderer::Object *to_return = stack.get_array()[last_obj_idx];
	
	stack.extract_from_end();

	return to_return;
}

Renderer::Object *Renderer::get_last()
{
	size_t last_obj_idx = stack.get_length() - 1;
	return stack.get_array()[last_obj_idx];
}

void Renderer::draw_circle(const Vector_ll &par_position, const double par_radius, const Color &par_color, const Color &par_fill_color)
{
	Renderer::Object *obj = get_last();

	sf::CircleShape circle(par_radius);

	Vector_ll absolute_pos = par_position + obj->offset;
	circle.setPosition(sf::Vector2f(absolute_pos.get_x(), absolute_pos.get_y()));

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	circle.setOutlineColor(color);
	circle.setFillColor(fill_color);

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(circle, blend);
}

void Renderer::draw_rectangle(const Vector_ll &par_position, const double par_width, const double par_height, const Color &par_color, const Color &par_fill_color)
{
	Renderer::Object *obj = get_last();

	sf::RectangleShape rectangle(sf::Vector2f(par_width, par_height));

	Vector_ll absolute_pos = par_position + obj->offset;
	rectangle.setPosition(sf::Vector2f(absolute_pos.get_x(), absolute_pos.get_y()));

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	rectangle.setOutlineColor(color);

	sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	rectangle.setFillColor(fill_color);

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(rectangle, blend);
}

void Renderer::draw_triangle(const Vector_ll &point1, const Vector_ll &point2, const Vector_ll &point3, const Color &par_color, const Color &par_fill_color)
{
	Renderer::Object *obj = get_last();
	
	sf::ConvexShape convex;

	convex.setPointCount(3);
	
	Vector_ll absolute_p1 = point1 + obj->offset;
	Vector_ll absolute_p2 = point2 + obj->offset;
	Vector_ll absolute_p3 = point3 + obj->offset;

	convex.setPoint(0, sf::Vector2f(absolute_p1.get_x(), absolute_p1.get_y()));
	convex.setPoint(1, sf::Vector2f(absolute_p2.get_x(), absolute_p2.get_y()));
	convex.setPoint(2, sf::Vector2f(absolute_p3.get_x(), absolute_p3.get_y()));

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	convex.setOutlineColor(color);

	sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	convex.setFillColor(fill_color);

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(convex, blend);
}

void Renderer::draw_point(const Vector_ll &point, const Color &par_color)
{
	Renderer::Object *obj = get_last();

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	
	Vector_ll absolute_pos = point + obj->offset;
	sf::Vertex sfml_point(sf::Vector2f(absolute_pos.get_x(), absolute_pos.get_y()), color);

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(&sfml_point, 1, sf::Points, blend);
}

void Renderer::draw_line(const Vector_ll &left, const Vector_ll &right, const Color &par_color)
{
	Renderer::Object *obj = get_last();

	Vector_ll absolute_left = left + obj->offset;
	Vector_ll absolute_right = right + obj->offset;

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	sf::Vertex sfml_line[] = {  sf::Vertex(sf::Vector2f(absolute_left.get_x(), absolute_left.get_y()), color), 
								sf::Vertex(sf::Vector2f(absolute_right.get_x(), absolute_right.get_y()), color) };
	
	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(sfml_line, 2, sf::Lines, blend);
}

void Renderer::draw_image(const Color *array, const Vector_ll &position, const size_t width, const size_t height)
{
	sf::Texture texture;
	texture.create(width, height);

	texture_load(&texture, array, width, height);

	draw_texture(position, &texture, width, height, 1);
}

void Renderer::draw_texture(const Vector_ll &position, const char *texture_name)
{
	Renderer::Object *obj = get_last();

	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile(texture_name);

	sprite.setTexture(texture);

	Vector_ll absolute_pos = position + obj->offset;
	sprite.setPosition(absolute_pos.get_x(), absolute_pos.get_y());

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(sprite, blend);
}

void Renderer::draw_texture(const Vector_ll &position, const sf::RenderTexture *texture, const size_t width, const size_t height, const double transperancy)
{
	const sf::Texture smpl_texture = texture->getTexture();
	draw_texture(position, &smpl_texture, width, height, transperancy);
}

void Renderer::draw_texture(const Vector_ll &position, const sf::Texture *texture, const size_t width, const size_t height, const double transperancy)
{
	Renderer::Object *obj = get_last();
	
	sf::Sprite sprite;

	size_t texture_width = texture->getSize().x;
	size_t texture_height = texture->getSize().y;

	Vector_ll absolute_pos = position + obj->offset;
	sprite.setPosition(absolute_pos.get_x(), absolute_pos.get_y());

	double scale_x = (double)width / (double)texture_width;
	double scale_y = (double)height / (double)texture_height;

	sprite.setTexture(*texture);
	sprite.setScale(scale_x, scale_y);

	sf::BlendMode blend = blending_mode(obj->mode);
	obj->render->draw(sprite, blend);
}

void Renderer::clear_texture(sf::RenderTexture *texture, const Color &color)
{
	texture->clear(sf::Color(color.r, color.g, color.b, color.a));
}

Color *Renderer::texture2data(sf::RenderTexture *texture, const size_t width, const size_t height)
{
	sf::Image image = (texture->getTexture()).copyToImage();

	Color *array = new Color[width * height];

	for (size_t i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			sf::Color pixel = image.getPixel(j, i);
			array[i * width + j] = *((Color*)&pixel);
		}
	}

	return array;
}

void Renderer::data2texture(sf::RenderTexture *texture, Color *data, const size_t width, const size_t height)
{
	sf::Texture tmp;
	tmp.create(width, height);
	tmp.update((sf::Uint8*)data, width, height, 0, 0); 
	
	sf::Sprite sprite;
	sprite.setTexture(tmp);

	texture->clear(sf::Color(255, 255, 255, 0));
	texture->draw(sprite);
	texture->display();
}
