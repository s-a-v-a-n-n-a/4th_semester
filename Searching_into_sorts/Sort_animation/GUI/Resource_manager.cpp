#include "Resource_manager.hpp"

// Resources * Resources::resources = nullptr;
// Resources_destroyer Resources::destroyer;

Resources::Resources() : textures() { ; }
Resources::~Resources()
{
	long long textures_amount = (long long)textures.get_length();

	for (long long i = textures_amount; i > 0; --i)
	{
		textures.delete_from_end();
	}
}

Full_texture *Resources::create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height)
{
	Full_texture *new_texture = nullptr;
	if (!texture_width || !texture_height)
		new_texture = new Full_texture(texture_name);
	else
		new_texture = new Full_texture(texture_name, texture_width, texture_height);

	textures.add_to_end(new_texture);

	return new_texture;
}

Full_texture *Resources::create_texture(Full_texture *other_texture)
{
	Full_texture *new_texture = nullptr;
	new_texture = new Full_texture(other_texture);

	textures.add_to_end(new_texture);

	return new_texture;
}

Full_texture *Resources::create_texture(const size_t texture_width, const size_t texture_height)
{
	Full_texture *new_texture = new Full_texture(texture_width, texture_height);

	textures.add_to_end(new_texture);

	return new_texture;
}

Animating_texture *Resources::create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height, const char *move_texture_name, const char *inactive_texture_name)
{
	Animating_texture *new_texture = nullptr;
	if (!texture_width || !texture_height)
		new_texture = new Animating_texture(texture_name);
	else
		new_texture = new Animating_texture(texture_name, texture_width, texture_height);

	if (move_texture_name)
		new_texture->set_move_texture(move_texture_name);
	if (inactive_texture_name)
		new_texture->set_inactive_texture(inactive_texture_name);
	
	textures.add_to_end(new_texture);

	return new_texture;
}

void Resources::delete_texture(Texture *texture)
{
	long long textures_amount = (long long)textures.get_length();
	for (long long i = 0; i < textures_amount; ++i)
	{
		if (textures.get_array()[i] == texture)
		{
			textures.slow_delete(i);
			break;
		}
	}
}

// Resources * Application::get_app()->get_rescrs() 
// {
// 	if (resources == nullptr)
// 	{
// 		resources = new Resources();
// 		destroyer.initialize(resources);
// 	}

// 	return resources;
// }

// Resources_destroyer::~Resources_destroyer() 
// { 
// 	delete resources; 
// }

// void Resources_destroyer::initialize(Resources *par_resources) 
// { 
// 	resources = par_resources; 
// }
