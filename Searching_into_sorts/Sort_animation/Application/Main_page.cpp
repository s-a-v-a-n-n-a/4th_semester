#include "Main_page.hpp"
// #include "Chart_delegates.hpp"
#include "Application.hpp"

const size_t START_X_COORD = 50;
const size_t START_Y_COORD = 50;

const size_t BAR_GRAPH_HEIGHT = 500;
const size_t BAR_GRAPH_WIDTH = 1000;

const size_t BUTTON_X_COORD = START_X_COORD;
const size_t BUTTON_SIZE = 200;

const size_t CLEAR_BUTTON_X_COORD = BUTTON_X_COORD + BUTTON_SIZE + 100;
const size_t CLEAR_BUTTON_Y_COORD = START_Y_COORD + BAR_GRAPH_HEIGHT;

const char *BUTTON_CHART_TEXTS[] = 
{
	" BUBBLE SORT ",
	" SELECTION SORT ",
	" INSERTION SORT ",
	" STD SORT ",
	// " STABLE SORT ",
	" MERGE SORT "
};

const char REFILL_BUTTON_TEXT[] = " REFILL ";

const Color BUTTON_COLORS[] = 
{
	RED,
	BLUE,
	GREEN,
	CYAN,
	PURPLE,
	GENTLE_ORANGE
};

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	Int_container *container = new Int_container(50);
	container->random_fill();
	Bar_graph *graph = create_bar_graph(Vector_ll(START_X_COORD, START_Y_COORD), Vector_ll(BAR_GRAPH_WIDTH, BAR_GRAPH_HEIGHT), WHITE, container);

	container->set_contact(graph);
	
	Button *button = nullptr;
	for (int i = 0; i < sorts_amount; ++i)
	{
		button = create_sort_button(Vector_ll(BUTTON_X_COORD + BAR_GRAPH_WIDTH, START_Y_COORD + i * INCREASED_BUTTON_HEIGHT), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), BUTTON_CHART_TEXTS[i], BUTTON_COLORS[i], container, standartised_sorts[i]);
	}

	Button *refill_button = create_refill_button(Vector_ll(BUTTON_X_COORD+ BAR_GRAPH_WIDTH, START_Y_COORD + (sorts_amount + 1) * INCREASED_BUTTON_HEIGHT), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), REFILL_BUTTON_TEXT, FUCHSIA, graph, container);
}

Bar_graph *Main_page::create_bar_graph(const Vector_ll &position, const Vector_ll &size, const Color &color, Int_container *array)
{
	Bar_graph *graph = new Bar_graph({this, 
										(size_t)Vidget_type::BAR_GRAPH,
										position,
										nullptr,
										color,
										(size_t)size.get_x(),
										(size_t)size.get_y()},
										array);

	add_visual_object(graph);

	return graph;
}

Button *Main_page::create_sort_button(const Vector_ll &position, const Vector_ll &size, const char *name, const Color &color, Int_container *array, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)))
{
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										nullptr,
    										color, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Sort_delegate *delegate = new Sort_delegate(array, sort);
	Button *sort_button = new Button(button_base, delegate, name);

	add_visual_object(sort_button);

	return sort_button;
}

Button *Main_page::create_refill_button(const Vector_ll &position, const Vector_ll &size, const char *name, const Color &color, Bar_graph *graph, Int_container *array)
{
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										nullptr,
    										color, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Refill_delegate *delegate = new Refill_delegate(array, graph);
	Button *refill_button = new Button(button_base, delegate, name);

	add_visual_object(refill_button);

	return refill_button;
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
	get_objects()->add_to_end(par_object); 
	par_object->set_visible(true);
	par_object->set_reactive(true);
}

bool Main_page::on_key_pressed(const bool pressed_state, const unsigned key_mask)
{
	Visual_object::on_key_pressed(pressed_state, key_mask);

	return false;
}
