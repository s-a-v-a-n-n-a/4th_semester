#include "Graphical_delegates.hpp"
#include "Application.hpp"

// // Interactive
// // ---------------------------------------------------------------------------------------------------------
// Interactive::Interactive(Visual_object *par_to_interact) 
// : to_interact(nullptr)
// {
// 	to_interact = par_to_interact;
// }

// bool Interactive::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	Color changing_color = to_interact->get_color();
// 	int new_a = (int)MAX_COLOR_VALUE;
	
// 	if (to_interact->point_inside(to.get_x(), to.get_y()))
// 	{
// 		changing_color.set_a(new_a * 3 / 4);
// 	}
// 	else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
// 	{
// 		changing_color.set_a(new_a);
// 	}

// 	to_interact->set_color(changing_color);

// 	return true;
// }

// void Interactive::set_interactive(Visual_object *par_to_interact)
// {
// 	to_interact = par_to_interact;
// }

// // ---------------------------------------------------------------------------------------------------------

// // Animating
// // ---------------------------------------------------------------------------------------------------------

// Animating::Animating(Visual_object *par_to_animate) 
// : to_animate(nullptr), move_in(nullptr), move_out(nullptr), move_in_index(-1), move_out_index(-1)
// {
// 	to_animate = par_to_animate;
// }

// void Animating::reset()
// {
// 	Full_texture *default_texture = ((Animating_texture*)(to_animate->get_texture()))->get_default_texture();
// 	((Animating_texture*)(to_animate->get_texture()))->set_current_texture(default_texture);
	
// 	if (move_in)
// 	{
// 		// Animation_manager::get_instance()->slow_delete_animation(move_in);
// 		Application::get_app()->get_animations()->slow_delete_animation(move_in);
// 		move_in = nullptr;
// 		move_in_index = -1;
// 	}

// 	if (move_out)
// 	{
// 		// Animation_manager::get_instance()->slow_delete_animation(move_out);
// 		Application::get_app()->get_animations()->slow_delete_animation(move_out);
// 		move_out = nullptr;
// 		move_out_index = -1;
// 	}
// }

// bool Animating::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	// Full_texture *default_texture = ((Animating_texture*)(to_animate->get_texture()))->get_default_texture();
// 	// ((Animating_texture*)(to_animate->get_texture()))->set_current_texture(default_texture);
	
// 	// if (move_in)
// 	// {
// 	// 	Animation_manager::get_instance()->slow_delete_animation(move_in);
// 	// 	move_in = nullptr;
// 	// 	move_in_index = -1;
// 	// }

// 	// if (move_out)
// 	// {
// 	// 	Animation_manager::get_instance()->slow_delete_animation(move_out);
// 	// 	move_out = nullptr;
// 	// 	move_out_index = -1;
// 	// }

// 	return true;
// }

// bool Animating::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	if (to_animate->point_inside(to.get_x(), to.get_y()) && !to_animate->point_inside(from.get_x(), from.get_y()))
// 	{
// 		if (!move_in)
// 		{
// 			if (move_out)
// 			{
// 				// Animation_manager::get_instance()->slow_delete_animation(move_out);
// 				Application::get_app()->get_animations()->slow_delete_animation(move_out);
// 				move_out = nullptr;
// 				move_out_index = -1;
// 			}

// 			move_in = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), 0.05);
// 			// move_in_index = Animation_manager::get_instance()->add_animation(move_in);
// 			move_in_index = Application::get_app()->get_animations()->add_animation(move_in);
// 		}
// 	}
// 	else if(!to_animate->point_inside(to.get_x(), to.get_y()) && to_animate->point_inside(from.get_x(), from.get_y()))
// 	{
// 		if (!move_out)
// 		{
// 			if (move_in)
// 			{
// 				// Animation_manager::get_instance()->slow_delete_animation(move_in);
// 				Application::get_app()->get_animations()->slow_delete_animation(move_in);
// 				move_in = nullptr;
// 				move_in_index = -1;
// 			}
			
// 			move_out = new Animation((Animating_texture*)to_animate->get_texture(), to_animate, ((Animating_texture*)(to_animate->get_texture()))->get_move_texture(), ((Animating_texture*)(to_animate->get_texture()))->get_default_texture(), 0.05);
// 			// move_out_index = Animation_manager::get_instance()->add_animation(move_out);
// 			move_out_index = Application::get_app()->get_animations()->add_animation(move_out);
// 		}
// 	}

// 	return true;
// }

// void Animating::set_animating(Visual_object *par_to_animate)
// {
// 	to_animate = par_to_animate;
// }
// // ---------------------------------------------------------------------------------------------------------

// // Magnetic
// // ---------------------------------------------------------------------------------------------------------
// // bool Magnetic::in_bounds(const size_t par_x, const size_t par_y)
// // {
// // 	if (par_x >= left_bound.get_x() && par_x <= right_bound.get_x()
// // 		&& par_y >= left_bound.get_y() && par_y <= right_bound.get_y())
// // 		return true;

// // 	return false;
// // }

// // bool Magnetic::on_mouse_click(const size_t par_x, const size_t par_y)
// // {
// // 	printf("mouse!!!\n");

// // 	if (!pressed)
// // 	{
// // 		pressed = true;

// // 		if (in_bounds(par_x, par_y))
// // 			to_control->set_position(Vector_ll(par_x, par_y));
// // 	}
// // 	else
// // 		pressed = false;

// // 	return true;
// // }

// // bool Magnetic::on_mouse_move(const Vector_ll from, const Vector_ll to)
// // {
// // 	printf("it is moving\n");

// // 	if (pressed && in_bounds(to.get_x(), to.get_y()))
// // 	{
// // 		to_control->set_position(to);

// // 		return true;
// // 	}
// // 	else if (!in_bounds(to.get_x(), to.get_y()))
// // 	{
// // 		pressed = false;

// // 		return false;
// // 	}
// // }
// // ---------------------------------------------------------------------------------------------------------

// // Restore_delegate
// // ---------------------------------------------------------------------------------------------------------
// Restore_delegate::Restore_delegate(Visual_object *par_to_restore)
// : to_restore(nullptr)
// {
// 	to_restore = par_to_restore;
// }

// bool Restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	// to_restore->set_visible(true);
// 	// to_restore->set_reactive(true);

// 	return true;
// }

// bool Restore_delegate::on_mouse_release()
// {
// 	to_restore->set_visible(true);
// 	to_restore->set_reactive(true);

// 	return true;
// }

// // Double click restore_delegate
// // ---------------------------------------------------------------------------------------------------------
// Double_click_restore_delegate::Double_click_restore_delegate(Visual_object *par_to_restore)
// : to_restore(par_to_restore), clicked_once(false)
// {
// 	;
// }

// bool Double_click_restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	// to_restore->set_visible(true);
// 	// to_restore->set_reactive(true);
// 	if (!clicked_once)
// 		clicked_once = true;
// 	else
// 		clicked_once = false;

// 	return true;
// }

// bool Double_click_restore_delegate::on_mouse_release()
// {
// 	if (clicked_once)
// 	{
// 		to_restore->set_visible(true);
// 		to_restore->set_reactive(true);

// 		to_restore->get_parent()->set_active(to_restore);
// 	}
// 	else
// 	{
// 		to_restore->set_visible(false);
// 		to_restore->set_reactive(false);
// 	}

// 	return true;
// }

// // ---------------------------------------------------------------------------------------------------------

// Animating_double_click_restore_delegate::Animating_double_click_restore_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact)
// : Double_click_restore_delegate(par_to_restore), Animating(par_to_interact) {}

// bool Animating_double_click_restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Double_click_restore_delegate::on_mouse_click(par_x, par_y);
// 	return Animating::on_mouse_click(par_x, par_y);
// }

// bool Animating_double_click_restore_delegate::on_mouse_release()
// {
// 	bool result = Double_click_restore_delegate::on_mouse_release();
// 	if (clicked_once)
// 		return Animating::on_mouse_release();
// 	else
// 		return result;
// }

// bool Animating_double_click_restore_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	bool result = false;
// 	if (!clicked_once)
// 		return Animating::on_mouse_move(from, to);
// 	else
// 		return result;
// }

// // ---------------------------------------------------------------------------------------------------------

// // Animating_restore_delegate
// // ---------------------------------------------------------------------------------------------------------

// Animating_restore_delegate::Animating_restore_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact)
// : Restore_delegate(par_to_restore), Animating(par_to_interact)
// {
// 	;
// }

// bool Animating_restore_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Restore_delegate::on_mouse_click(par_x, par_y);
// 	return Animating::on_mouse_click(par_x, par_y);
// }

// bool Animating_restore_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	return Animating::on_mouse_move(from, to);
// }

// // ---------------------------------------------------------------------------------------------------------


// // Restore_interactive_delegate
// // ---------------------------------------------------------------------------------------------------------
// Restore_interactive_delegate::Restore_interactive_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact) 
// : Restore_delegate(par_to_restore), Interactive(par_to_interact)
// {
// 	;
// }

// bool Restore_interactive_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	return Interactive::on_mouse_move(from, to);
// }
// // ---------------------------------------------------------------------------------------------------------


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

// // Animating_roll_up_delegate
// // ---------------------------------------------------------------------------------------------------------
// Animating_roll_up_delegate::Animating_roll_up_delegate(Visual_object *par_to_roll_up, Visual_object *par_to_interact)
// : Roll_up_delegate(par_to_roll_up), Animating(par_to_interact)
// {
// 	;
// }

// bool Animating_roll_up_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Roll_up_delegate::on_mouse_click(par_x, par_y);
// 	return Animating::on_mouse_click(par_x, par_y);
// }

// bool Animating_roll_up_delegate::on_mouse_release()
// {
// 	Animating::reset();
// 	return Roll_up_delegate::on_mouse_release();
// }

// bool Animating_roll_up_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	return Animating::on_mouse_move(from, to);
// }
// // ---------------------------------------------------------------------------------------------------------

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


// // Close_interactive_delegate 
// // ---------------------------------------------------------------------------------------------------------
// Close_interactive_delegate::Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact) 
// : Close_delegate(par_to_close), to_interact(nullptr)
// {
// 	to_interact = par_to_interact;
// }

// bool Close_interactive_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	Color changing_color = to_interact->get_color();
// 	int new_a = (int)MAX_COLOR_VALUE;
	
// 	if (to_interact->point_inside(to.get_x(), to.get_y()))
// 	{
// 		changing_color.set_a(new_a * 3 / 4);
// 	}
// 	else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
// 	{
// 		changing_color.set_a(new_a);
// 	}

// 	to_interact->set_color(changing_color);

// 	return true;
// }
// // ---------------------------------------------------------------------------------------------------------

// Animating_close_delegate::Animating_close_delegate(Visual_object *par_to_close, Visual_object *par_to_interact)
// : Close_delegate(par_to_close), Animating(par_to_interact)
// {}

// bool Animating_close_delegate::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Close_delegate::on_mouse_click(par_x, par_y);
// 	return Animating::on_mouse_click(par_x, par_y);
// }
// bool Animating_close_delegate::on_mouse_release()
// {
// 	Animating::reset();
// 	return Close_delegate::on_mouse_release();
// }
// bool Animating_close_delegate::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	return Animating::on_mouse_move(from, to);
// }

// ---------------------------------------------------------------------------------------
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

// // One_dim_move
// // ---------------------------------------------------------------------------------------------------------

// One_dim_move::One_dim_move(Visual_object *par_to_change_place, const bool par_x_dimension) 
// : to_change_place(par_to_change_place), clicked(false), first_position(0, 0), last_position(0, 0), x_dimension(par_x_dimension)
// {
// 	;
// }

// bool One_dim_move::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	clicked = true;

// 	first_position = Vector_ll(par_x, par_y);

// 	return true;
// }

// bool One_dim_move::on_mouse_release()
// {
// 	clicked = false;

// 	first_position = last_position;

// 	return true;
// }

// bool One_dim_move::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	// if (to_change_place->point_inside(to.get_x(), to.get_y()))
// 	// {
// 	// 	clicked = false;
// 	// 	return false;
// 	// }

// 	if (clicked)
// 	{
// 		last_position = to;

// 		Vector_ll new_position = to_change_place->get_position() + to - from;
// 		if (x_dimension)
// 			new_position.set_y(to_change_place->get_position().get_y());
// 		else
// 			new_position.set_x(to_change_place->get_position().get_x());

// 		bool bad_position = false;

// 		if (new_position.get_x() < 0)
// 		{
// 			new_position.set_x(0);
// 			bad_position = true;
// 		}
// 		if (new_position.get_y() < 0)
// 		{
// 			new_position.set_y(0);
// 			bad_position = true;
// 		}

// 		if (bad_position)
// 			on_mouse_release();

// 		to_change_place->set_position(new_position);
// 		first_position = last_position;

// 		return true;
// 	}

// 	return false;
// }

// // ----------------------------------------------------------------------------------------------------------------------------

// Change_fixedly::Change_fixedly(Visual_object *par_to_control, const long long par_delta, const bool par_change_x)
// : to_control(par_to_control), delta(par_delta), change_x(par_change_x)
// {
// 	;
// }

// bool Change_fixedly::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Vector_ll last_position = to_control->get_position();
	
// 	if (change_x)
// 	{
// 		to_control->set_position(last_position + Vector_ll(delta, 0));
// 	}
// 	else
// 	{
// 		to_control->set_position(last_position + Vector_ll(0, delta));
// 	}

// 	return true;
// }

// // ----------------------------------------------------------------------------------------------------------------------------

// Animating_change_fixedly::Animating_change_fixedly(Visual_object *par_to_control, const long long par_delta, const bool par_change_x, Visual_object *par_to_animate)
// : Change_fixedly(par_to_control, par_delta, par_change_x), Animating(par_to_animate) {}

// bool Animating_change_fixedly::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	Change_fixedly::on_mouse_click(par_x, par_y);
// 	return Animating::on_mouse_click(par_x, par_y);
// }
// bool Animating_change_fixedly::on_mouse_release()
// {
// 	Change_fixedly::on_mouse_release();
// 	return Animating::on_mouse_release();
// }
// bool Animating_change_fixedly::on_mouse_move(const Vector_ll from, const Vector_ll to)
// {
// 	return Animating::on_mouse_move(from, to);
// }

// // Roll_up_confirmation
// // ----------------------------------------------------------------------------------------------------------------------------

// Roll_up_confirmation::Roll_up_confirmation(Visual_object *par_roll_up)
// : to_roll_up(par_roll_up)
// {}

// bool Roll_up_confirmation::on_mouse_click(const size_t par_x, const size_t par_y)
// {
// 	return true;
// }
// bool Roll_up_confirmation::on_mouse_release()
// {
// 	// delete to_roll_up;
// 	to_roll_up->set_alive(false);
// 	// Application::get_app()->set_default();
	
// 	return true;
// }
