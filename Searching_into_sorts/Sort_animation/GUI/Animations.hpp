#ifndef ANIMATIONS_AND_MANAGER_H
#define ANIMATIONS_AND_MANAGER_H

#include "../Graphical_wrapper/screen_functions.hpp"
#include "../Graphical_wrapper/Texture.hpp"
#include "../GUI/Visual_object_base.hpp"

#include "../Graphical_wrapper/Animating_texture.hpp"

// class Animation_manager; 

class Animation
{
private:
	Animating_texture *to_store;

	Full_texture *texture_from;
	Full_texture *texture_to;

	Visual_object *changable;
	double delta_time;

	double current_time;

	bool alive;

public:
	Animation(Animating_texture *par_to_store, Visual_object *par_changable, Full_texture *par_from, Full_texture *par_to, const double par_delta_time);
	~Animation() = default;

	void set_alive(const bool par_alive) { alive = par_alive; }
	bool get_alive() const { return alive; }

	Visual_object *get_changable() { return changable; }
	Animating_texture *get_to_store() { return to_store; }

	void tick(const double time);
};

// class Animation_manager_destroyer
// {
// private:
// 	Animation_manager *animation_manager;
// public:
// 	~Animation_manager_destroyer();

// 	void initialize(Animation_manager *par_animation_manager);
// };

class Animation_manager
{
private:
	// static Animation_manager *animation_manager;
	// static Animation_manager_destroyer destroyer;
	List<Animation*> animations;

// protected:
public:
	Animation_manager();
	~Animation_manager();
	// friend class Animation_manager_destroyer;

// public:
	// static Animation_manager *get_instance();

	long long add_animation(Animation *par_animation);
	void slow_delete_animation(Animation *to_delete);

	void tick(const double time);
	// void draw(Screen_information *screen);
};

#endif // ANIMATIONS_AND_MANAGER_H
