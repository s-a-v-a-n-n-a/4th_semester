#include "Main_page.hpp"
#include "Chart_delegates.hpp"
#include "Graphical_delegates.hpp"
#include "Application.hpp"

#ifdef WITH_SPLINE
const size_t DEFAULT_CANVAS_SIZE = 300;
#else
const size_t DEFAULT_CANVAS_SIZE = 1100;
#endif

const size_t DEFAULT_COLOR_VIDGET_WIDTH = 400 + 20;
const size_t DEFAULT_COLOR_VIDGET_HEIGHT = 400 + 20 + 90; //  + DEFAULT_BUTTON_HEIGHT
const size_t DEFAULT_COLOR_VIDGET_POS_X = 0;
const size_t DEFAULT_COLOR_VIDGET_POS_Y = INCREASED_BUTTON_HEIGHT;

const size_t DEFAULT_SIZE_VIDGET_POS_X = 0;
const size_t DEFAULT_SIZE_VIDGET_POS_Y = DEFAULT_COLOR_VIDGET_HEIGHT + DEFAULT_COLOR_VIDGET_POS_Y;

const size_t THICKNESS_WINDOW_WIDTH = 400;
const size_t THICKNESS_WINDOW_HEIGHT = 100;
const size_t THICKNESS_WINDOW_POS_X = 0;
const size_t THICKNESS_WINDOW_POS_Y = INCREASED_BUTTON_HEIGHT;

const size_t TOOLS_BAR_WIDTH = 300;
const size_t TOOLS_BAR_HEIGHT = 1000;

const size_t DEFAULT_CANVAS_POS_X = THICKNESS_WINDOW_WIDTH;
const size_t DEFAULT_CANVAS_POS_Y = INCREASED_BUTTON_HEIGHT;

// const size_t DEFAULT_BUTTON_WIDTH = 200;

const size_t DEFAULT_TEXT_OFFSET = 20;

const char BUBBLE_TEXT[] = " BUBBLE SORT ";
const char SELECTION_TEXT[] = " SELECTION SORT ";

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	// Full_texture *chart_background = Application::get_app()->get_rescrs()->create_texture(CHART_BACKGROUND, 500, 500);
	Chart_window *chart1 = create_chart_window(Vector_ll(200, 200), Vector_ll(400, 400), WHITE);
	Button *bubble = create_control_button(chart1, BUBBLE_TEXT, Vector_ll(200, 600), Vector_ll(400, 80), GREEN, bubble_sort);

	Chart_window *chart2 = create_chart_window(Vector_ll(700, 200), Vector_ll(400, 400), WHITE);
	Button *selection = create_control_button(chart2, SELECTION_TEXT, Vector_ll(700, 600), Vector_ll(400, 80), BLUE, selection_sort);
}

Chart_window *Main_page::create_chart_window(const Vector_ll &position, const Vector_ll &size, const Color &color)
{
	Chart_window *chart = new Chart_window({this, 
											(size_t)Vidget_type::CHART_WINDOW,
											position,
											nullptr,
											color,
											(size_t)size.get_x(),
											(size_t)size.get_y()});

	add_visual_object(chart);

	return chart;
}

Button *Main_page::create_control_button(Chart_window *chart, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)))
{
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										nullptr,
    										color, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Button *new_button = new Button(button_base,
								  	nullptr, 
								  	text,
								  	true);
	Generate_chart *delegate = new Generate_chart(chart, color, sort);
	new_button->set_delegate(delegate);

	add_visual_object(new_button);

	return new_button;
}

Main_page::~Main_page()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

void Main_page::add_visual_object(Visual_object *par_object) 
{ 
	// printf("\n\nadded\n\n");

	get_objects()->add_to_end(par_object); 
	par_object->set_visible(true);
	par_object->set_reactive(true);
}

bool Main_page::on_key_pressed(const bool pressed_state, const unsigned key_mask)
{
	Visual_object::on_key_pressed(pressed_state, key_mask);

	return false;
}
