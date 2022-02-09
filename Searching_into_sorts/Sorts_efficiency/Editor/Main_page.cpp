#include "Main_page.hpp"
#include "Chart_delegates.hpp"
#include "Application.hpp"

const size_t DEFAULT_BUTTON_OFFSET = 20;

const size_t START_X_COORD = 100;
const size_t START_Y_COORD = 100;
const size_t CHART_SIZE = 400;
const size_t CHART_OFFSET = 50;

const size_t BUTTON_X_COORD = 1000;
const size_t BUTTON_SIZE = 200;

const char *BUTTON_CHART_TEXTS[] = 
{
	" BUBBLE SORT ",
	" SELECTION SORT ",
	" STD SORT ",
	" STABLE SORT ",
	" QUICK SORT ",
	" MERGE SORT "
};

const char *CHARTS_TEXTS[] =
{
	"Assignments -> amount",
	"Comparisons -> amount"
};

const Color BUTTON_COLORS[] = 
{
	RED,
	FUCHSIA,
	BLUE,
	CYAN,
	PURPLE,
	GENTLE_ORANGE
};

const char CLEAR_TEXT[] = " CLEAR ";
const char DATA_TEXT[] = " RESET DATA ";

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	std::vector<Chart_window*> charts;
	for (int i = 0; i < 2; ++i)
	{
		Chart_window *chart = create_chart_window(Vector_ll(START_X_COORD + i * (CHART_SIZE + CHART_OFFSET), START_Y_COORD), Vector_ll(CHART_SIZE, CHART_SIZE), WHITE, CHARTS_TEXTS[i]);
		charts.push_back(chart);
	}
	
	Button *button = nullptr;
	for (int i = 0; i < sorts_amount; ++i)
	{
		button = create_control_button(charts[0], charts[1], BUTTON_CHART_TEXTS[i], Vector_ll(BUTTON_X_COORD, START_Y_COORD + i * (INCREASED_BUTTON_HEIGHT + DEFAULT_BUTTON_OFFSET)), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), BUTTON_COLORS[i], i, standartised_sorts[i]);
	}

	create_clear_button(charts, CLEAR_TEXT, Vector_ll(BUTTON_X_COORD, START_Y_COORD + (sorts_amount + 1) * (INCREASED_BUTTON_HEIGHT + DEFAULT_BUTTON_OFFSET)), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), MEDIUM_PURPLE);
	create_regeneration_button(DATA_TEXT, Vector_ll(BUTTON_X_COORD, START_Y_COORD + (sorts_amount + 2) * (INCREASED_BUTTON_HEIGHT + DEFAULT_BUTTON_OFFSET)), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), MEDIUM_PURPLE);
}

Chart_window *Main_page::create_chart_window(const Vector_ll &position, const Vector_ll &size, const Color &color, const char *name)
{
	Chart_window *chart = new Chart_window({this, 
											(size_t)Vidget_type::CHART_WINDOW,
											position,
											nullptr,
											color,
											(size_t)size.get_x(),
											(size_t)size.get_y()}, 
											name);

	add_visual_object(chart);

	return chart;
}

Button *Main_page::create_control_button(Chart_window *chart_ass, Chart_window *chart_cmp, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color, size_t colored_texture_number, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)))
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(COLORED_BUTTONS[colored_texture_number], size.get_x(), size.get_y(), COLORED_BUTTONS_MOVE[colored_texture_number], nullptr);
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										texture,
    										TRANSPARENT, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };
	
	Button *new_button = new Button(button_base,
								  	nullptr, 
								  	text,
								  	true);
	
	Animating_generate_graph *ass_delegate = new Animating_generate_graph(chart_ass, color, Research::ASSIGNMENT, sort, new_button);	
	Generate_chart *cmp_delegate = new Generate_chart(chart_cmp, color, Research::COMPARISON, sort);
	
	new_button->set_delegate(ass_delegate);
	new_button->set_delegate(cmp_delegate);
	
	add_visual_object(new_button);

	return new_button;
}

Button *Main_page::create_clear_button(std::vector<Chart_window*> charts, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color)
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(GREEN_BUTTON, size.get_x(), size.get_y(), GREEN_BUTTON_MOVE, nullptr);
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										texture,
    										TRANSPARENT, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Button *new_button = new Button(button_base,
										nullptr, 
										text,
										true);
	size_t charts_amount = charts.size();									
	Animating_clear_field *delegate = nullptr;
	for (int i = 0; i < charts_amount; ++i)
	{
		delegate = new Animating_clear_field(charts[i], new_button);
		new_button->set_delegate(delegate);
	}

	add_visual_object(new_button);

	return new_button;
}

Button *Main_page::create_regeneration_button(const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color)
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(GREEN_BUTTON, size.get_x(), size.get_y(), GREEN_BUTTON_MOVE, nullptr);
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										texture,
    										TRANSPARENT, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Button *new_button = new Button(button_base,
										nullptr, 
										text,
										true);
	Animating_regenerate_data *delegate = new Animating_regenerate_data(new_button);
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
