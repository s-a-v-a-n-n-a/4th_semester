#include "Button.hpp"

const size_t DEFAULT_BUTTON_HEIGHT = 50;
const size_t INCREASED_BUTTON_HEIGHT = 70;
const size_t DEFAULT_BUTTON_WIDTH = 200;

Button::Button(const Visual_object::Config &base, Button_delegate *par_click)
: Visual_object(base), pressed(false)
{
	if (par_click)
		clicks.push_back(par_click);
}

Button::Button(const Visual_object::Config &base, Button_delegate *par_click, const char *par_text, const bool centered)
: Visual_object(base), pressed(false)
{
	if (par_click)
		clicks.push_back(par_click);
	
	size_t offset = get_height() / 2;
	Text *text = nullptr;
	if (centered)
	{
		text = new Text(this, (size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							get_position() + Vector_ll(get_width()/2, get_height()/2), //par_position + 
							DEFAULT_TEXT_COLOR,
							centered);
	}
	else
	{
		text = new Text(this, (size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							get_position() + Vector_ll(10, get_height()/2), //par_position + 
							DEFAULT_TEXT_COLOR,
							centered);
	}
	add_visual_object(text);
}

Button::~Button()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}

	long long delegates_amount = clicks.size();
	for (long long i = delegates_amount - 1; i >= 0; --i)
	{
		delete clicks[i];
		clicks.pop_back();
	}
}

void Button::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->draw(screen);
	}
}

bool Button::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		set_active_state(true);
	    
	    bool result = false;
		if (state)
		{
			for (int i = 0; i < clicks.size(); ++i)
			{
				result = clicks[i]->on_mouse_click(par_x, par_y);
				if (result)
					pressed = true;
			}
		}
		else if (pressed)
		{ 
			for (int i = 0; i < clicks.size(); ++i)
			{
				result = clicks[i]->on_mouse_release();
				if (result)
					pressed = false;
			}
		}
	    	
	    // Visual_object::on_mouse_click(state, par_x, par_y);
		return true;
	}
	else
	{
	    // Visual_object::on_mouse_click(state, par_x, par_y);
		return false;
	}
}

bool Button::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool result = false;
	
	bool from_in = point_inside(from.get_x(), from.get_y());
	bool to_in = point_inside(to.get_x(), to.get_y());

	if (from_in || to_in)
	{
		if (to_in)
			set_active_state(true);
		for (int i = 0; i < clicks.size(); ++i)
		{
			result = clicks[i]->on_mouse_move(from, to);
		}
	}
	else
	{
		result = false;
	}

	if (!point_inside(to.get_x(), to.get_y()))
		pressed = false;

	// Visual_object::on_mouse_move(from, to);
	return result;
}

Magnetic::Magnetic(const Visual_object::Config &par_base, Visual_object *par_parent, const Vector_ll &par_left_bound, const Vector_ll &par_right_bound, const size_t par_radius, Button_delegate *par_delegate)
: Visual_object(par_base), parent(par_parent), left_bound(par_left_bound), right_bound(par_right_bound), pressed(false), radius(par_radius), delegate(par_delegate)
{
	last_parent_position = parent->get_position();

	// задать relation
	if (right_bound.get_x() - left_bound.get_x())
		x_relation = (double)get_position().get_x() / (double)(right_bound.get_x() - left_bound.get_x());
	else
		x_relation = 0;

	if (right_bound.get_y() - left_bound.get_y())
		y_relation = (double)get_position().get_y() / (double)(right_bound.get_y() - left_bound.get_y());
	else
		y_relation = 0;
}

void Magnetic::set_x_relation(const double par_x_relation)
{
	if (par_x_relation > 1 || par_x_relation < 0)
		return;

	x_relation = par_x_relation;

	size_t max_width = right_bound.get_x() - left_bound.get_x();
	size_t x_position = (size_t)((double)max_width * par_x_relation);
	
	set_position(Vector_ll(left_bound.get_x() + x_position, get_position().get_y()));
}

void Magnetic::set_y_relation(const double par_y_relation)
{
	if (par_y_relation > 1 || par_y_relation < 0)
		return;

	y_relation = par_y_relation;

	size_t max_height = right_bound.get_y() - left_bound.get_y();
	size_t y_position = (size_t)((double)max_height * par_y_relation);
	
	set_position(Vector_ll(get_position().get_x(), y_position));
}

void Magnetic::set_position(const Vector_ll &par_position)
{
	Vector_ll offset = parent->get_position() - last_parent_position;
	last_parent_position = parent->get_position();
	
	Visual_object::set_position(get_position() + offset);
	left_bound += offset;
	right_bound += offset;

	size_t par_x = par_position.get_x();
	size_t par_y = par_position.get_y();

	bool in_x = in_x_bounds(par_x, par_y);
	bool in_y = in_y_bounds(par_x, par_y);

	if ((!in_x) || (!in_y))
		return;
	
	Visual_object::set_position(par_position);

	x_relation = ((double)right_bound.get_x() - (double)par_position.get_x()) / ((double)right_bound.get_x() - (double)left_bound.get_x());
	y_relation = ((double)right_bound.get_y() - (double)par_position.get_y()) / ((double)right_bound.get_y() - (double)left_bound.get_y());
	// Vector_ll offset = par_position - get_position();

	// if (delegate)
	// 	delegate->on_mouse_click(offset.get_x(), offset.get_y());
}

bool Magnetic::in_x_bounds(const size_t par_x, const size_t par_y)
{
	if (par_x >= left_bound.get_x() && par_x <= right_bound.get_x() && (left_bound.get_y() - (long long)par_y) <= (long long)radius && ((long long)par_y - right_bound.get_y()) <= (long long)radius)
		return true;

	return false;
}

bool Magnetic::in_y_bounds(const size_t par_x, const size_t par_y)
{
	if (par_y >= left_bound.get_y() && par_y <= right_bound.get_y() && (left_bound.get_x() - (long long)par_x) <= (long long)radius && ((long long)par_x - right_bound.get_x()) <= (long long)radius)
	{
		return true;
	}

	return false;
}

bool Magnetic::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (state)
	{
		pressed = true;

		bool in_x = in_x_bounds(par_x, par_y);
		bool in_y = in_y_bounds(par_x, par_y);

		if (in_x && in_y)
		{
			set_position(Vector_ll(par_x, par_y));

			return true;
		}
		else if (in_x)
		{
			set_position(Vector_ll(par_x, get_position().get_y()));

			return true;
		}
		else if (in_y)
		{
			set_position(Vector_ll(get_position().get_x(), par_y));

			return true;
		}

		pressed = false;
		return false;
	}
	else
	{
		pressed = false;
	}

	return true;
}

bool Magnetic::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// printf("it is moving: %d\n", in);
	if (pressed)
	{
		bool in_x = in_x_bounds(to.get_x(), to.get_y());
		bool in_y = in_y_bounds(to.get_x(), to.get_y());
		
		if (in_x || in_y)
		{
			if (in_x && in_y)
			{
				set_position(to);
			}
			else if (in_x)
			{
				set_position(Vector_ll(to.get_x(), get_position().get_y()));
			}
			else if (in_y)
			{
				set_position(Vector_ll(get_position().get_x(), to.get_y()));
			}

			return true;
		}
		else
			return false;
	}
	else// if (!in_bounds(to.get_x(), to.get_y()))
	{
		pressed = false;

		return false;
	}
}
