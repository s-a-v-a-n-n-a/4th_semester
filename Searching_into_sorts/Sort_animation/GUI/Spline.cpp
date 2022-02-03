#include "Spline.hpp"

const size_t DECREASED_DOT_SIZE = 5;
const size_t DEFAULT_DOT_SIZE = 20;

Spline::Spline(const Visual_object::Config &par_base, Button_delegate *par_delegate, const Vector_ll &par_high_limit, const Vector_ll &par_low_limit)
: Visual_object(par_base), first(nullptr), last(nullptr), points(get_width(), 0), delegate(par_delegate), high_limit(par_high_limit), low_limit(par_low_limit)
{
	// first = new Magnetic({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, get_height()) - Vector_ll(0, DEFAULT_DOT_SIZE), nullptr, BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE}, get_position() - Vector_ll(0, DEFAULT_DOT_SIZE), get_position() + Vector_ll(0, get_height()) - Vector_ll(0, DEFAULT_DOT_SIZE), DEFAULT_DOT_SIZE/2);

	first = new Button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, get_height()) - Vector_ll(0, DEFAULT_DOT_SIZE), nullptr, BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE}, NULL, "");
	One_dim_move *left_drag = new One_dim_move(first, false);
	first->set_delegate(left_drag);

	get_objects()->add_to_end(first);

	// last = create_spline_dot(get_position() + Vector_ll(get_width(), 0) - Vector_ll(DEFAULT_DOT_SIZE, 0), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);
	// last = new Magnetic({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(get_width(), 0) - Vector_ll(DEFAULT_DOT_SIZE, 0), nullptr, BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE}, get_position() + Vector_ll(get_width(), 0) - Vector_ll(DEFAULT_DOT_SIZE, 0), get_position() + Vector_ll(get_width(), get_height()) - Vector_ll(DEFAULT_DOT_SIZE, 0), DEFAULT_DOT_SIZE/2);
	last = new Button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(get_width(), 0) - Vector_ll(DEFAULT_DOT_SIZE, 0), nullptr, BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE}, NULL, "");
	One_dim_move *right_drag = new One_dim_move(last, false);
	last->set_delegate(right_drag);
	
	add_visual_object(last);
}

Button *Spline::create_spline_dot(const Vector_ll &position, const size_t width, const size_t height)
{
	Button *dot = new Button({this, (size_t)Vidget_type::BUTTON, position, nullptr, BLACK, width, height}, NULL, "");
	Drag_and_drop_delegate *drag = new Drag_and_drop_delegate(dot);
	dot->set_delegate(drag);

	add_visual_object(dot);

	return dot;
}

Interpolator *Spline::create_interpolator()
{
	std::vector<Vector_d> reference_points;

	size_t points_amount = get_objects()->get_length();
	Visual_object **points_array = get_objects()->get_array();
	
	for (size_t i = 0; i < points_amount; ++i)
	{
		reference_points.push_back(Vector_d((double)(points_array[i]->get_position().get_x() - get_position().get_x()), (double)(points_array[i]->get_position().get_y() - get_position().get_y())));
	}
	
	Interpolator *interpolator = new Interpolator(reference_points);

	return interpolator;
}

void Spline::recount(Interpolator *interpolator)
{
	size_t width = get_width();
	size_t last_reference = 0;
	for (size_t i = DEFAULT_DOT_SIZE/2; i < width - DEFAULT_DOT_SIZE/2; ++i)
	{
		Vector_d point_d = interpolator->get_point(i, &last_reference);
		points[i] = point_d;
	}
}

void Spline::add_visual_object(Visual_object *par_object)
{
	Interpolator *interpolator = create_interpolator();
	interpolator->add_point(Vector_d((double)(par_object->get_position().get_x() - get_position().get_x()), (double)(par_object->get_position().get_y() - get_position().get_y())));
	
	recount(interpolator);

	delete interpolator;

	get_objects()->add_to_end(par_object);
}

void Spline::draw(Screen_information *screen)
{
	size_t points_amount = get_width();
	for (size_t i = DEFAULT_DOT_SIZE; i < points_amount - DEFAULT_DOT_SIZE - 1; ++i)
	{
		size_t y1 = (size_t)points[i].get_y() + get_position().get_y() + DEFAULT_DOT_SIZE/2;

		screen->draw_line(Vector_ll((size_t)points[i].get_x() + get_position().get_x() + DEFAULT_DOT_SIZE/2, (size_t)points[i].get_y() + get_position().get_y() + DEFAULT_DOT_SIZE/2), Vector_ll((size_t)points[i + 1].get_x() + get_position().get_x() + DEFAULT_DOT_SIZE/2, (size_t)points[i + 1].get_y() + get_position().get_y() + DEFAULT_DOT_SIZE/2), get_color());
	}
	
	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (objects_array[i]->get_visible())
		{
			objects_array[i]->draw(screen);
		}
	}
}

Vector_ll Spline::create_relation(const double par_x, const double par_y)
{
	double scale_x = ((par_x) / ((double)get_width() - (double)DEFAULT_DOT_SIZE));
	double scale_y = ((par_y) / ((double)get_height() - (double)DEFAULT_DOT_SIZE));

	// printf("scale y %lg\n", scale_y);
	double max_x = (double)(high_limit.get_x() - low_limit.get_x());
	double max_y = (double)(high_limit.get_y() - low_limit.get_y());

	return Vector_ll((long long)(((double)(max_x)) * scale_x) + low_limit.get_x(), (long long)(((double)(max_y)) * scale_y) + low_limit.get_y());
}

void Spline::transfer_graph()
{
	size_t width = get_width();
	size_t height = get_height();
	size_t go = (width - DEFAULT_DOT_SIZE) / MAX_COLOR_VALUE;
	// size_t go = 1;
	if (go < 1)
		go = 1;
	for (size_t i = DEFAULT_DOT_SIZE/2; i < width - DEFAULT_DOT_SIZE/2 - 1; i += go)	
	{
		Vector_ll par = create_relation(points[i].get_x(), height - DEFAULT_DOT_SIZE - points[i].get_y());

		// if (par.get_x() == 255)
		// {
		// 	printf("%lld\n", par.get_y());
		// }
		// printf("%lld %lld\n", par.get_x(), par.get_y());
		delegate->on_mouse_click(par.get_x(), par.get_y());
	}
}

bool Spline::on_mouse_click (const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
		size_t points_amount = get_objects()->get_length();
		
		bool clicked = false;
		for (long long i = (long long)points_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y))
			{
				transfer_graph();
				return true;
			}
			set_active_state(false);
		}

		Interpolator *interpolator = create_interpolator();
		size_t reference_index = 0;
		Vector_d check_point = interpolator->get_point((double)par_x - get_position().get_x(), &reference_index);

		if (check_point.get_y() + DEFAULT_DOT_SIZE >= par_y - get_position().get_y() && check_point.get_y() - DEFAULT_DOT_SIZE <= par_y - get_position().get_y())
		{
			Button *new_dot = create_spline_dot(Vector_ll(par_x, par_y), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);

			transfer_graph();
			return true;
		}
	}

	return false;
}

bool Spline::on_mouse_move (const Vector_ll from, const Vector_ll to)
{
	bool standart_result = false;

	if (get_reactive() && point_inside(to.get_x(), to.get_y()))
	{
		size_t objects_amount = get_objects()->get_length();

		bool move_got = false;
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			Visual_object *obj = (get_objects()->get_array()[i]);
			move_got = obj->on_mouse_move(from, to);

			if (move_got)
			{
				move_to_end(get_objects()->get_array()[i], i);
				
				standart_result = true;
				break;
			}
		}
	}

	if (standart_result && delegate)
	{
		transfer_graph();
	}

	return standart_result;
}

void Spline::tick(const double delta)
{
	// assert(screen);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		Visual_object *obj = objects_array[i];

		if (obj == first || obj == last)
			continue;

		Vector_ll obj_position = obj->get_position();
		if (!obj->get_alive() || obj_position.get_x() <= get_position().get_x() || obj_position.get_y() <= get_position().get_y() 
			|| obj_position.get_x() + obj->get_width() >= get_position().get_x() + get_width() || obj_position.get_y() + obj->get_height() >= get_position().get_y() + get_height())
		{
			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}

		// obj->tick(delta);
	}
}
