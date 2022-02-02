#include "Animations.hpp"

Animation::Animation(Animating_texture *par_to_store, Visual_object *par_changable, Full_texture *par_from, Full_texture *par_to, const double par_delta_time)
: changable(par_changable), to_store(par_to_store), texture_from(par_from), texture_to(par_to), delta_time(par_delta_time), current_time(0), alive(true)
{ 
	// changable->set_texture(nullptr);
	;
}

void Animation::tick(const double time)
{
	// printf("time %lg\n", current_time);

	if (current_time > 1)
	{
		set_alive(false);
		
		return;
	}

	current_time += delta_time;

	(*(to_store->get_current_texture())).clear(sf::Color(255, 255, 255, 0));

	sf::Sprite sprite_from;
	sprite_from.setTexture(*texture_from->get_texture());
	sprite_from.setColor(sf::Color(255, 255, 255, (unsigned char)(255 * (1 - current_time))));

	sf::Sprite sprite_to;
	sprite_to.setTexture(*texture_to->get_texture());
	sprite_to.setColor(sf::Color(255, 255, 255, (unsigned char)(255 * current_time)));

	(*(to_store->get_current_texture())).draw(sprite_from);
	(*(to_store->get_current_texture())).draw(sprite_to);
	(*(to_store->get_current_texture())).display();
}

// Animation manager
// ---------------------------------------------------------------------------------------------------------------

// Animation_manager * Animation_manager::animation_manager = nullptr;
// Animation_manager_destroyer Animation_manager::destroyer;

Animation_manager::Animation_manager() : animations() { ; }
Animation_manager::~Animation_manager() 
{ 
	long long animations_amount = (long long)animations.get_length();

	for (long long i = animations_amount; i >= 0; --i)
	{
		animations.delete_from_end();
	}
}

// Animation_manager * Animation_manager::get_instance() 
// {
// 	if (animation_manager == nullptr)
// 	{
// 		animation_manager = new Animation_manager();
// 		destroyer.initialize(animation_manager);
// 	}

// 	return animation_manager;
// }

long long Animation_manager::add_animation(Animation *par_animation)
{
	par_animation->set_alive(true);
	animations.add_to_end(par_animation); 

	return animations.get_length() - 1;
}

void Animation_manager::slow_delete_animation(Animation *to_delete)
{
	// Animation **animations_array = animations.get_array();
	// (animations_array[index]->get_changable())->set_texture(animations_array[index]->get_to_store());

	Animation **animations_array = animations.get_array();
	size_t objects_amount = animations.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (to_delete == animations_array[i])
		{
			animations.slow_delete(i); 
			break;
		}
	}
}

void Animation_manager::tick(const double time)
{
	Animation **animations_array = animations.get_array();
	size_t objects_amount = animations.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (!animations_array[i]->get_alive())
		{
			// slow_delete_animation(i)
			animations.slow_delete(i);
			i--;
			objects_amount--;
			continue;
		}

		animations_array[i]->tick(time);
	}
}

// Animation_manager_destroyer::~Animation_manager_destroyer() 
// { 
// 	delete animation_manager; 
// }

// void Animation_manager_destroyer::initialize(Animation_manager *par_animation_manager) 
// { 
// 	animation_manager = par_animation_manager; 
// }

