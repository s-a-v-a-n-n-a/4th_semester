#include "Main_page.hpp"
// #include "Chart_delegates.hpp"
#include "Application.hpp"

const size_t BUTTON_SIZE = 200;

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	Int_container *container = new Int_container(10);
	container->random_fill();
	Bar_graph *graph = create_bar_graph(Vector_ll(50, 50), Vector_ll(1000, 500), WHITE, container);

	container->set_contact(graph);

	Button *sort_button = create_sort_button(Vector_ll(50, 600), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), FUCHSIA, container, bubble_sort);
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

Button *Main_page::create_sort_button(const Vector_ll &position, const Vector_ll &size, const Color &color, Int_container *array, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)))
{
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										nullptr,
    										color, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Sort_delegate *delegate = new Sort_delegate(array, sort);
	Button *sort_button = new Button(button_base, delegate, " SORT ");

	add_visual_object(sort_button);

	return sort_button;
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
