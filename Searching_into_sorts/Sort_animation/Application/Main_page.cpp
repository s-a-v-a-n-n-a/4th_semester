#include "Main_page.hpp"
// #include "Chart_delegates.hpp"
#include "Application.hpp"

Main_page::Main_page(const Visual_object::Config &par_base)
: Visual_object(par_base)
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	// Full_texture *chart_background = Application::get_app()->get_rescrs()->create_texture(CHART_BACKGROUND, 500, 500);
	std::vector<Chart_window*> charts;
	for (int i = 0; i < 2; ++i)
	{
		Chart_window *chart = create_chart_window(Vector_ll(START_X_COORD + i * (CHART_SIZE + CHART_OFFSET), START_Y_COORD), Vector_ll(CHART_SIZE, CHART_SIZE), WHITE, CHARTS_TEXTS[i]);
		charts.push_back(chart);
	}
	
	// Button *selection = create_control_button(charts[0], charts[1], SELECTION_TEXT, Vector_ll(700, 600), Vector_ll(400, 80), BLUE, selection_sort);
	// Button *sort = create_control_button(charts[0], charts[1], STD_SORT_TEXT, Vector_ll(700, 680), Vector_ll(400, 80), RED, std_sort);
	// Button *stablesort = create_control_button(charts[0], charts[1], STABLE_SORT_TEXT, Vector_ll(700, 760), Vector_ll(400, 80), PURPLE, std_stable_sort);
	// Button *std_qsort = create_control_button(charts[0], charts[1], QUICK_SORT_TEXT, Vector_ll(700, 840), Vector_ll(400, 80), FUCHSIA, qsort);
	// Button *merge_sort = create_control_button(charts[0], charts[1], MERGE_SORT_TEXT, Vector_ll(700, 920), Vector_ll(400, 80), GENTLE_ORANGE, wrapped_merge_sort);
	// Button *bubble = create_control_button(charts[0], charts[1], BUBBLE_TEXT, Vector_ll(200, 600), Vector_ll(400, 80), GREEN, bubble_sort);
	Button *button = nullptr;
	for (int i = 0; i < sorts_amount; ++i)
	{
		button = create_control_button(charts[0], charts[1], BUTTON_CHART_TEXTS[i], Vector_ll(BUTTON_X_COORD, START_Y_COORD + i * INCREASED_BUTTON_HEIGHT), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), BUTTON_COLORS[i], standartised_sorts[i]);
	}

	Button *clear = create_clear_button(charts, CLEAR_TEXT, Vector_ll(BUTTON_X_COORD, 900), Vector_ll(BUTTON_SIZE, INCREASED_BUTTON_HEIGHT), MEDIUM_PURPLE);
	// Button *clear2 = create_clear_button(charts, CLEAR_TEXT, Vector_ll(700, 1200), Vector_ll(400, 80), MEDIUM_PURPLE);
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

Button *Main_page::create_control_button(Chart_window *chart_ass, Chart_window *chart_cmp, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color, void (*sort)(void *, size_t, size_t, int(*cmp)(const void *, const void *)))
{
	Visual_object::Config button_base = { this, 
											(size_t)Vidget_type::BUTTON,
    										position, 
    										nullptr,
    										color, 
								  			(size_t)size.get_x(), 
								  			(size_t)size.get_y() };

	Generate_chart *ass_delegate = new Generate_chart(chart_ass, color, Research::ASSIGNMENT, sort);	
	Generate_chart *cmp_delegate = new Generate_chart(chart_cmp, color, Research::COMPARISON, sort);
	
	Button *new_button = new Button(button_base,
								  	nullptr, 
								  	text,
								  	true);
	new_button->set_delegate(ass_delegate);
	new_button->set_delegate(cmp_delegate);
	
	add_visual_object(new_button);

	return new_button;
}

Button *Main_page::create_clear_button(std::vector<Chart_window*> charts, const char *text, const Vector_ll &position, const Vector_ll &size, const Color &color)
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
	size_t charts_amount = charts.size();									
	Clear_field *delegate = nullptr;
	for (int i = 0; i < charts_amount; ++i)
	{
		delegate = new Clear_field(charts[i]);
		new_button->set_delegate(delegate);
	}

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
