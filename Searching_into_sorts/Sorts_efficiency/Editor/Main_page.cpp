#include "Main_page.hpp"
#include "Chart_delegates.hpp"
#include "Application.hpp"

#ifdef WITH_SPLINE
const size_t DEFAULT_CANVAS_SIZE = 300;
#else
const size_t DEFAULT_CANVAS_SIZE = 1100;
#endif

const size_t DEFAULT_TEXT_OFFSET = 20;

const char BUBBLE_TEXT[] = " BUBBLE SORT ";
const char SELECTION_TEXT[] = " SELECTION SORT ";
const char STD_SORT_TEXT[] = " STD SORT ";
const char STABLE_SORT_TEXT[] = " STABLE SORT ";
const char QUICK_SORT_TEXT[] = " QUICK SORT ";
const char MERGE_SORT_TEXT[] = " MERGE SORT ";
const char CLEAR_TEXT[] = " CLEAR ";

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	// Full_texture *chart_background = Application::get_app()->get_rescrs()->create_texture(CHART_BACKGROUND, 500, 500);
	Chart_window *chart1 = create_chart_window(Vector_ll(200, 200), Vector_ll(400, 400), WHITE, "Comparing sorts");
	Button *bubble = create_control_button(chart1, BUBBLE_TEXT, Vector_ll(200, 600), Vector_ll(400, 80), GREEN, bubble_sort);
	Button *clear1 = create_clear_button(chart1, CLEAR_TEXT, Vector_ll(200, 1200), Vector_ll(400, 80), MEDIUM_PURPLE);

	Chart_window *chart2 = create_chart_window(Vector_ll(700, 200), Vector_ll(400, 400), WHITE, "Comparing sorts");
	Button *selection = create_control_button(chart2, SELECTION_TEXT, Vector_ll(700, 600), Vector_ll(400, 80), BLUE, selection_sort);
	Button *sort = create_control_button(chart2, STD_SORT_TEXT, Vector_ll(700, 680), Vector_ll(400, 80), RED, std_sort);
	Button *stablesort = create_control_button(chart2, STABLE_SORT_TEXT, Vector_ll(700, 760), Vector_ll(400, 80), PURPLE, std_stable_sort);
	Button *std_qsort = create_control_button(chart2, QUICK_SORT_TEXT, Vector_ll(700, 840), Vector_ll(400, 80), FUCHSIA, qsort);
	Button *merge_sort = create_control_button(chart2, MERGE_SORT_TEXT, Vector_ll(700, 920), Vector_ll(400, 80), GENTLE_ORANGE, wrapped_merge_sort);
	
	Button *clear2 = create_clear_button(chart2, CLEAR_TEXT, Vector_ll(700, 1200), Vector_ll(400, 80), MEDIUM_PURPLE);
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

Button *Main_page::create_clear_button(Chart_window *chart, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color)
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
	Clear_field *delegate = new Clear_field(chart);
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
