#include "Application.hpp"

const size_t DEFAULT_SIZE = 1300;
const size_t DEFAULT_HEIGHT = 800;

Application *Application::app = nullptr;
Application_destroyer Application::destroyer;

Application::Application()
: current_main(nullptr), default_main(nullptr), graphics_wrapper(nullptr)
{
    app = this;

    renderer = new Renderer();
    graphics_wrapper = new Screen_information(DEFAULT_SIZE, DEFAULT_HEIGHT);

    animations = new Animation_manager();
    resources = new Resources();

    Main_page *editor = new Main_page({nullptr, (size_t)Vidget_type::EDITOR, Vector_ll(0, 0), nullptr, DARK_GREY, DEFAULT_SIZE, DEFAULT_HEIGHT});
    default_main = editor;
    current_main = default_main;

    printf("[Application] : end of initialization\n");
}

Application::~Application()
{
    delete animations;
    delete graphics_wrapper;
    delete renderer;

	delete default_main;
}

Application *Application::get_app()
{
	if (app == nullptr)
	{
		new Application();
		destroyer.initialize(app);
	}

	return app;
}

Visual_object * Application::get_default()
{
    return default_main;
}

Visual_object * Application::get_main()
{
    return current_main;
}

void Application::set_default()
{
	current_main = default_main;
}

void Application::set_main(Visual_object *object)
{
	current_main = object;
}

Renderer *Application::get_renderer()
{
    return renderer;
}

Resources *Application::get_rescrs()
{
    return resources;
}

Animation_manager *Application::get_animations()
{
    return animations;
}

void Application::add_visual_object(Visual_object *object)
{
    default_main->add_visual_object(object);
}

void Application::draw()
{
	default_main->draw(graphics_wrapper);

	if (current_main != default_main)
    {
		graphics_wrapper->draw_rectangle({0, 0}, default_main->get_width(), default_main->get_height(), {100, 100, 100, 150}, {100, 100, 100, 150});
        current_main->draw(graphics_wrapper);
    }
}

void Application::tick()
{
    animations->tick(0.005);
	
	default_main->tick(0.05); // graphics_wrapper, 0.05

	if (current_main != default_main)
    {
		if (!(current_main->get_alive()))
        {
            delete current_main;
            set_default();
            return;
        }
        current_main->tick(0.05); // graphics_wrapper, 0.05
    }

    // plugins->tick(0.5);
}

void Application::launch()
{
    // plugins->load_from_dir("Plugins/");

    Vector_ll click_place(0, 0);

	bool open = true;
    Event result = { Event_type::NO_EVENT, 0, 0 };
    while(open)
    {
        unsigned key_state = 0;
        graphics_wrapper->reset();
                
        do
        {
            result = graphics_wrapper->event_handler.detect_event(graphics_wrapper->window, graphics_wrapper->event);

            switch (result.type)
            {
            case Event_type::WINDOW:
                graphics_wrapper->window.close();
                open = false;
                break;

            case Event_type::MOUSE:
            {
                switch (result.event)
                {
                case (size_t)Mouse_state::CLICKED:
                    click_place = graphics_wrapper->get_mouse_position();
                    current_main->on_mouse_click(true, result.position.get_x(), result.position.get_y());

                    break;
                
                case (size_t)Mouse_state::RELEASED:
                    click_place = graphics_wrapper->get_mouse_position();
                    current_main->on_mouse_click(false, result.position.get_x(), result.position.get_y());

                    break;
                case (size_t)Mouse_state::MOVED:
                {
                    Vector_ll move_place(graphics_wrapper->get_mouse_position());
                    current_main->on_mouse_move(click_place, result.position);
                    click_place = move_place;

                    break;
                }
                default:
                    break;
                }
                
                break;
            }
            case Event_type::TEXT:
                current_main->on_text_entered((char)result.event);

                break;
            case Event_type::KEYBOARD:
                switch (result.event)
                {
                case (size_t)Key_state::PRESSED:
                    key_state |= result.sender;
                    current_main->on_key_pressed(true, key_state);

                    break;

                case (size_t)Key_state::RELEASED:
                    key_state |= result.sender;
                    current_main->on_key_pressed(false, key_state);

                    break;

                default:
                    break;
                }

            default:
                break;
            }

        }while(result.type != Event_type::NO_EVENT);

        tick();
        draw();
        
        graphics_wrapper->sfml_update_mouse_state();

        graphics_wrapper->window.display();
    }
}


Application_destroyer::~Application_destroyer() 
{ 
	delete app; 
}

void Application_destroyer::initialize(Application *par_app) 
{ 
	app = par_app; 
}
