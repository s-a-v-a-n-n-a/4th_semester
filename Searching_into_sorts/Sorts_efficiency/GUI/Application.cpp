#include "../GUI/Resource_manager.hpp"

Application *Application::app = nullptr;
Application_destroyer Application::app_destroyer;

Application::Application() 
{ 
	resources = new Resources(); 
	animation_manager = new Animation_manager();

	editor = new Graphical_editor_main_page({this, (size_t)Vidget_type::EDITOR, Vector_ll(0, 0), nullptr, DARK_GREY, DEFAULT_SIZE, DEFAULT_SIZE});
}
Application::~Application()
{
	delete editor;

	delete animation_manager;
	delete resources;
}

Application *Application::get_app() 
{
	if (app == nullptr)
	{
		app = new Application();
		app_destroyer.initialize(app);
	}

	return app;
}

Resources *Application::get_resources()
{
	return resources;
}

Animation_manager *Application::get_animation()
{
	return animation_manager;
}

void Application::launch()
{
	Screen_information screen(DEFAULT_SIZE, DEFAULT_SIZE);

    bool open = true;
    while(open)
    {
        unsigned key_state = 0;
        screen.reset();
        
        Sfml_events result = screen.event_handler.detect_event(screen.window, screen.event);
        switch (result)
        {
        case Sfml_events::WINDOW_CLOSED:
            screen.window.close();
            open = false;
            break;

        case Sfml_events::MOUSE_CLICKED:
        {
            click_place = screen.get_mouse_position();
            editor->on_mouse_click(true, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_RELEASED:
        {
            click_place = screen.get_mouse_position();

            editor->on_mouse_click(false, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_MOVED:
        {
            Vector_ll move_place(screen.get_mouse_position());
            editor->on_mouse_move(click_place, move_place);
            click_place = move_place;

            break;
        }

        case Sfml_events::KEY_U:
            key_state |= (unsigned)Key_state::KEY_U;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_R:
            key_state |= (unsigned)Key_state::KEY_R;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_G:
            key_state |= (unsigned)Key_state::KEY_G;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_B:
            key_state |= (unsigned)Key_state::KEY_B;
            
            editor->on_key_pressed(key_state);

            break;

        default:
            break;
        }

        tick(&screen, 0.005);
        draw(&screen);
        
        screen.sfml_update_mouse_state();

        screen.window.display();
    }
}

void Application::tick(Screen_information *screen, const double time)
{
	animation_manager->tick(time);
    editor->tick(screen, time);
}

void Application::draw(Screen_information *screen)
{
    editor->draw(&screen);
}

// --------------------------------------------------------------------------------------------------------------------
// Animation manager
// --------------------------------------------------------------------------------------------------------------------

Animation_manager::Animation_manager() : animations() { ; }
Animation_manager::~Animation_manager() 
{ 
	long long animations_amount = (long long)animations.get_length();

	for (long long i = animations_amount; i >= 0; --i)
	{
		animations.delete_from_end();
	}
}

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

// --------------------------------------------------------------------------------------------------------------------
// Resources manager
// --------------------------------------------------------------------------------------------------------------------

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
	Full_texture *new_texture = new Full_texture(texture_name, texture_width, texture_height);

	textures.add_to_end(new_texture);

	return new_texture;
}

Animating_texture *Resources::create_texture(const char *texture_name, const size_t texture_width, const size_t texture_height, const char *move_texture_name, const char *inactive_texture_name)
{
	Animating_texture *new_texture = new Animating_texture(texture_name, texture_width, texture_height);
	if (move_texture_name)
		new_texture->set_move_texture(move_texture_name);
	if (inactive_texture_name)
		new_texture->set_inactive_texture(inactive_texture_name);
	
	textures.add_to_end(new_texture);

	return new_texture;
}

// --------------------------------------------------------------------------------------------------------------------
// destroyer
// --------------------------------------------------------------------------------------------------------------------

Application_destroyer::~Application_destroyer() 
{ 
	delete app; 
}

void Application_destroyer::initialize(Application *par_app) 
{ 
	app = par_app; 
}

