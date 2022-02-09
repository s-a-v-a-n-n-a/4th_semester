#include "Graphical_delegates.hpp"
#include "Application.hpp"

// ---------------------------------------------------------------------------------------------------------
// Animating
// ---------------------------------------------------------------------------------------------------------

Animating::Animating(Visual_object *par_to_animate) 
: to_animate(nullptr), move_in(nullptr), move_in_index(-1), move_out(nullptr), move_out_index(-1)
{
	to_animate = par_to_animate;
}

void Animating::reset()
{
	Full_texture *default_texture = ((Animating_texture*)(to_animate->get_texture()))->get_default_texture();
	((Animating_texture*)(to_animate->get_texture()))->set_current_texture(default_texture);
	
	if (move_in)
	{
		// Animation_manager::get_instance()->slow_delete_animation(move_in);
		Application::get_app()->get_animations()->slow_delete_animation(move_in);
		move_in = nullptr;
		move_in_index = -1;
	}

	if (move_out)
	{
		// Animation_manager::get_instance()->slow_delete_animation(move_out);
		Application::get_app()->get_animations()->slow_delete_animation(move_out);
		move_out = nullptr;
		move_out_index = -1;
	}
}

bool Animating::on_mouse_click(const size_t par_x, const size_t par_y)
{
	return true;
}

bool Animating::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (to_animate->point_inside(to.get_x(), to.get_y()) && !to_animate->point_inside(from.get_x(), from.get_y()))
	{
		if (!move_in)
		{
			if (move_out)
			{
				// Animation_manager::get_instance()->slow_delete_animation(move_out);
				Application::get_app()->get_animations()->slow_delete_animation(move_out);
				move_out = nullptr;
				move_out_index = -1;
			}

			move_in = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), 0.01);
			// move_in_index = Animation_manager::get_instance()->add_animation(move_in);
			move_in_index = Application::get_app()->get_animations()->add_animation(move_in);
		}
	}
	else if(!to_animate->point_inside(to.get_x(), to.get_y()) && to_animate->point_inside(from.get_x(), from.get_y()))
	{
		if (!move_out)
		{
			if (move_in)
			{
				// Animation_manager::get_instance()->slow_delete_animation(move_in);
				Application::get_app()->get_animations()->slow_delete_animation(move_in);
				move_in = nullptr;
				move_in_index = -1;
			}
			
			move_out = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), 0.01);
			// move_out_index = Animation_manager::get_instance()->add_animation(move_out);
			move_out_index = Application::get_app()->get_animations()->add_animation(move_out);
		}
	}

	return true;
}

void Animating::set_animating(Visual_object *par_to_animate)
{
	to_animate = par_to_animate;
}

// ---------------------------------------------------------------------------------------------------------
// Roll_up_delegate
// ---------------------------------------------------------------------------------------------------------

Roll_up_delegate::Roll_up_delegate(Visual_object *par_to_roll_up)
: to_roll_up(nullptr)
{
	to_roll_up = par_to_roll_up;
}

bool Roll_up_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	return true;
}

bool Roll_up_delegate::on_mouse_release()
{
	to_roll_up->set_visible(false);
	to_roll_up->set_reactive(false);

	return true;
}

Visual_object *Roll_up_delegate::get_roll_up() { return to_roll_up; }

// ---------------------------------------------------------------------------------------------------------
// Animating_roll_up_delegate
// ---------------------------------------------------------------------------------------------------------

Animating_roll_up_delegate::Animating_roll_up_delegate(Visual_object *par_to_roll_up, Visual_object *par_to_interact)
: Roll_up_delegate(par_to_roll_up), Animating(par_to_interact)
{
	;
}

bool Animating_roll_up_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Roll_up_delegate::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_roll_up_delegate::on_mouse_release()
{
	Animating::reset();
	return Roll_up_delegate::on_mouse_release();
}

bool Animating_roll_up_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}

// ---------------------------------------------------------------------------------------------------------
// Close_delegate
// ---------------------------------------------------------------------------------------------------------

Close_delegate::Close_delegate(Visual_object *par_to_close)
: to_close(nullptr)
{
	to_close = par_to_close;
}

bool Close_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	return true;
}

bool Close_delegate::on_mouse_release()
{
	to_close->set_alive(false);

	return true;
}

// ---------------------------------------------------------------------------------------------------------
// Drag_and_drop_delegate
// ---------------------------------------------------------------------------------------------------------

Drag_and_drop_delegate::Drag_and_drop_delegate(Visual_object *par_to_change_place) 
: to_change_place(nullptr), clicked(false), first_position(0, 0), last_position(0, 0)
{
	to_change_place = par_to_change_place;
}

bool Drag_and_drop_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
{
	clicked = true;

	first_position = Vector_ll(par_x, par_y);

	// to_change_place->set_reactive(false);

	return true;
}

bool Drag_and_drop_delegate::on_mouse_release()
{
	clicked = false;

	first_position = last_position;

	// to_change_place->set_reactive(true);

	return true;
}

bool Drag_and_drop_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// if (to_change_place->point_inside(to.get_x(), to.get_y()))
	// {
	// 	clicked = false;
	// 	return false;
	// }

	if (clicked)
	{
		last_position = to;

		// printf("last: x %lld, y %lld; new: x %lld, y %lld\n", to_change_place->get_position().get_x(), to_change_place->get_position().get_y(), (to_change_place->get_position() + last_position - first_position).get_x(), (to_change_place->get_position() + last_position - first_position).get_y());

		// Vector_ll new_position = to_change_place->get_position() + last_position - first_position;
		Vector_ll new_position = to_change_place->get_position() + (to - from) / 2;
		bool bad_position = false;

		if (new_position.get_x() < 0)
		{
			new_position.set_x(0);
			bad_position = true;
		}
		if (new_position.get_y() < 0)
		{
			new_position.set_y(0);
			bad_position = true;
		}

		if (bad_position || !to_change_place->point_inside(from.get_x(), from.get_y()))
			on_mouse_release();

		to_change_place->set_position(new_position);
		first_position = last_position;

		return true;
	}
	else
		clicked = false;

	return false;
}
