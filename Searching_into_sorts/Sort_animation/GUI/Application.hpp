#ifndef APPLICATION_H
#define APPLICATION_H

class Application;

#include "Graphical_editor_main_page.hpp"
#include "../sfml_drawing/screen_functions.hpp"
#include "../GUI/Animations.hpp"

#include "../sfml_drawing/Texture.hpp"
#include "../sfml_drawing/Animating_texture.hpp"
#include "../simple_list/simple_list.hpp" 

#include "../GUI/Visual_object_base.hpp"

const size_t DEFAULT_SIZE = 1800;

class Application_destroyer
{
private:
	Application *app;

public:
	~Application_destroyer();

	void initialize(Application *par_app);
};

class Application
{
private:
	static Application *app;
	static Application_destroyer app_destroyer;

	Graphical_editor_main_page *editor;

	class Resources
	{
	private:
		// static Resources *resources;
		List<Texture*> textures;

	public:
		Resources();
		~Resources();

		Resources *get_instance();

		Full_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height);
		Animating_texture *create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height, const char *move_texture_name, const char *inactive_texture_name);
	};
	Resources *resources;

	class Animation_manager
	{
	private:
		// static Animation_manager *animation_manager;
		List<Animation*> animations;

	public:
		Animation_manager();
		~Animation_manager();

		Animation_manager *get_instance();

		long long add_animation(Animation *par_animation);
		void slow_delete_animation(Animation *to_delete);

		void tick(const double time);
	};
	Animation_manager *animation_manager;

protected:
	Application();
	~Application();

public:
	static Application *get_app();
	Resources *get_resources();
	Animation_manager *get_animation();

	void tick(Screen_information *screen, const double time);
	void draw(Screen_information *screen);
	void launch();
};

#endif // APPLICATION_H
