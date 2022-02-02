#include "Texture.hpp"
#include "screen_functions.hpp"

Texture::Texture(const size_t width, const size_t height)
: texture_name(nullptr), size(width, height)
{
	;
}

Texture::Texture(const char *par_texture_name) : texture_name(nullptr), size(0, 0)
{
	unsigned texture_length = strlen(par_texture_name) + 1;

	texture_name = new char[texture_length];
	memset(texture_name, 0, texture_length);
	strncpy(texture_name, par_texture_name, texture_length - 1);

	sf::Texture texture;
	texture.loadFromFile(par_texture_name);
	sf::Vector2u sfml_size = texture.getSize();

	size = Vector_ll(sfml_size.x, sfml_size.y);
}

Texture::~Texture()
{
	delete [] texture_name;
}

void Texture::set_size(const Vector_ll par_size) 
{ 
	size = par_size;
}


Full_texture::Full_texture(const size_t width, const size_t height)
: Texture(width, height)
{
	texture.create(width, height);
	texture.clear(sf::Color(255, 255, 255, 0));
	// texture.draw(sprite);
	texture.display();
}

Full_texture::Full_texture(const char *par_texture_name) : Texture(par_texture_name)
{
	tmp_texture.loadFromFile(par_texture_name);
	
	sf::Sprite sprite;
	sprite.setTexture(tmp_texture);

	// double scale_x = (double)width / (double)get_width();
	// double scale_y = (double)height / (double)get_height();

	// set_size(Vector_ll(width, height));
	// // render_texture.draw(texture);
	// if (scale_x > 1 || scale_y > 1)
	// {
	// 	tmp_texture.setSmooth(true);
	// }

	sprite.setTexture(tmp_texture);
	// sprite.setScale(scale_x, scale_y);

	// texture.create(width, height);
	texture.create(get_width(), get_height());
	texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite);
	texture.display();
}

Full_texture::Full_texture(const char *par_texture_name, const size_t width, const size_t height) : Texture(par_texture_name)
{
	tmp_texture.loadFromFile(par_texture_name);
	
	sf::Sprite sprite;
	// sprite.setTexture(tmp_texture);

	double scale_x = (double)width / (double)get_width();
	double scale_y = (double)height / (double)get_height();

	set_size(Vector_ll(width, height));
	// render_texture.draw(texture);
	if (scale_x > 1 || scale_y > 1)
	{
		tmp_texture.setSmooth(true);
	}

	sprite.setTexture(tmp_texture);
	sprite.setScale(scale_x, scale_y);

	texture.create(width, height);
	texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite);
	texture.display();
}

Full_texture::Full_texture(Full_texture *other)
: Texture(other->get_name())
{
	char *name = other->get_name();
	size_t width = other->get_width();
	size_t height = other->get_height();

	tmp_texture.loadFromFile(name);
	
	sf::Sprite sprite;

	double scale_x = (double)width / (double)get_width();
	double scale_y = (double)height / (double)get_height();

	set_size(Vector_ll(width, height));
	if (scale_x > 1 || scale_y > 1)
	{
		tmp_texture.setSmooth(true);
	}

	sprite.setTexture(tmp_texture);
	sprite.setScale(scale_x, scale_y);

	texture.create(width, height);
	texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite);
	texture.display();

	Color *other_data = other->get_pixels();
	set_texture(other_data, width, height);
	
}

Color *Full_texture::get_pixels()
{
	sf::Image image = (*get_texture()).copyToImage();

	size_t width = size.get_x();
	size_t height = size.get_y();

	Color *array = new Color[width * height];

	for (size_t i = 0; i < size.get_y(); ++i)
	{
		for (int j = 0; j < size.get_x(); ++j)
		{
			sf::Color pixel = image.getPixel(j, i);
			array[i * width + j] = *((Color*)&pixel);
		}
	}

	return array;
}

const Shelled_texture *Full_texture::get_texture()
{ 
	return &(texture.getTexture()); 
}

sf::RenderTexture *Full_texture::get_current_texture() 
{ 
	return &texture;
}

void Full_texture::set_size(const Vector_ll par_size)
{
	sf::Sprite sprite;
	
	sf::Texture other_texture;
	other_texture.loadFromFile(texture_name);
	sf::Vector2u sfml_size = other_texture.getSize();
	size = Vector_ll(sfml_size.x, sfml_size.y);

	long long width = par_size.get_x();
	long long height = par_size.get_y();

	// double scale_x = (double)width / (double)get_width();
	// double scale_y = (double)height / (double)get_height();

	sprite.setTexture(other_texture);
	// sprite.setScale(scale_x, scale_y);

	// texture.clear(sf::Color(255, 255, 255, 0));
	// texture.draw(sprite);
	// texture.display();
	// if (scale_x > scale_y)
	// 	scale_x = scale_y;
	// else
	// 	scale_y = scale_x;

	texture.create(width, height);
	texture.clear();
	texture.draw(sprite);
	texture.display();
	texture.getTexture().copyToImage().saveToFile("b.png");

	Texture::set_size(par_size);
}

void Full_texture::set_texture(const sf::Texture *par_texture) 
{ 
	// printf("-_________-\n");

	sf::Sprite sprite;
	sprite.setTexture(*par_texture);

	texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite);
	texture.display();
}

void Full_texture::set_texture(Color *array, const size_t width, const size_t height)
{ 
	sf::Texture tmp;
	tmp.create(width, height);
	tmp.update((sf::Uint8*)array, width, height, 0, 0); 
	
	sf::Sprite sprite;
	sprite.setTexture(tmp);

	texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite);
	texture.display();
}

void Full_texture::add_picture(Color *other_array, const size_t width, const size_t height, const sf::BlendMode &mode)
{
	// sf::Texture tmp;
	// tmp.create(width, height);
	// tmp.update((sf::Uint8*)array, width, height, 0, 0); 

	sf::Texture other_tmp;
	other_tmp.create(width, height);
	other_tmp.update((sf::Uint8*)other_array, width, height, 0, 0); 

	sf::Sprite sprite;

	// sf::RenderTexture render_texture;
	// render_texture.create(get_width(), get_height());

	// size_t texture_width = other_tmp->getSize().x;
	// size_t texture_height = other_tmp->getSize().y;

	// double scale_x = (double)width / (double)texture_width;
	// double scale_y = (double)height / (double)texture_height;

	sprite.setTexture(other_tmp);
	sprite.setPosition(0, 0);
	// sprite.setScale(scale_x, scale_y);

	// sf::BlendMode blend = blending_mode(mode);

	// texture.clear(sf::Color(255, 255, 255, 0));
	texture.draw(sprite, mode);
	texture.display();
	// texture.getTexture().copyToImage().saveToFile("b.png");
}

void Full_texture::add_texture(Full_texture *other_texture, const sf::BlendMode &mode)
{
	sf::Sprite sprite;

	sprite.setTexture(other_texture->get_current_texture()->getTexture());
	sprite.setPosition(0, 0);
	
	texture.draw(sprite, mode);
	texture.display();
	// texture.getTexture().copyToImage().saveToFile("b.png");
}

void Full_texture::clear()
{
	texture.clear(sf::Color(255, 255, 255, 0));
	texture.display();
}

