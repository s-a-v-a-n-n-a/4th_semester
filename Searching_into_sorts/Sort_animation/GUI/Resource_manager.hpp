#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../Graphical_wrapper/Texture.hpp"
#include "../Graphical_wrapper/Animating_texture.hpp"
#include "../simple_list/simple_list.hpp" 

// class Resources;

// class Resources_destroyer
// {
// private:
// 	Resources *resources;
// public:
// 	~Resources_destroyer();

// 	void initialize(Resources *par_resources);
// };

class Resources
{
private:
	// static Resources *resources;
	// static Resources_destroyer destroyer;
	List<Texture*> textures;

// protected:
public:
	Resources();
	~Resources();
	// friend class Resources_destroyer;

// public:
	// static Resources *get_instance();

	Full_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height);
	Full_texture *create_texture(Full_texture *other_texture);
	Full_texture *create_texture(const size_t texture_width, const size_t texture_height);
	Animating_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height, const char *move_texture_name, const char *inactive_texture_name);

	void delete_texture(Texture *texture);
};
#endif // RESOURCE_MANAGER_H
