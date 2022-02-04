#include "Visual_object_base.hpp"
#include "../Application/Application.hpp"

// const size_t VIDGETS_AMOUNT = 9;

Visual_object::Visual_object(const Visual_object::Config &par_base)
: objects(), base(par_base), current_active(nullptr), active(false), visible(true), reactive(true), alive(true)
{
	;
}

void Visual_object::add_visual_object(Visual_object *par_object) 
{ 
	objects.add_to_end(par_object); 
}

void Visual_object::slow_delete_visual_object(size_t index) 
{ 
	Application::get_app()->get_rescrs()->delete_texture(objects.get_array()[index]->get_texture());
	objects.slow_delete(index); 
}

long long Visual_object::very_slow_delete_visual_object(Visual_object *par_object)
{
	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if(objects_array[i] == par_object)
		{
			Application::get_app()->get_rescrs()->delete_texture(par_object->get_texture());
			objects.slow_delete(i);
			
			return i;
		}
	}

	return -1;
}

long long Visual_object::very_slow_extract_visual_object(Visual_object *par_object)
{
	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if(objects_array[i] == par_object)
		{
			Application::get_app()->get_rescrs()->delete_texture(par_object->get_texture());
			objects.extract(i);
			
			return i;
		}
	}

	return -1;
}

void Visual_object::set_position(const Vector_ll &par_position)
{
	Vector_ll offset = par_position - get_position();
	base.position = par_position;

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		objects_array[i]->set_position(objects_array[i]->get_position() + offset);
	}
}

void Visual_object::set_width (const size_t par_width)            
{ 
	base.width = par_width; 

	if (base.texture)
		base.texture->set_size({ (long long)par_width, base.texture->get_height() });
}

void Visual_object::set_height (const size_t par_height)           
{ 
	base.height = par_height;

	if (base.texture)
		base.texture->set_size({ base.texture->get_width(), (long long)par_height }); 
}

void Visual_object::draw(Screen_information *screen)
{
	// assert(screen);

	screen->draw_rectangle(get_position(), get_width(), get_height(), get_color(), get_color());
	if (base.texture)
		screen->draw_texture(get_position(), base.texture->get_texture(), get_width(), get_height());


	// if (get_reactive())
	// {
		Visual_object **objects_array = objects.get_array();
		size_t objects_amount = objects.get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->draw(screen);
			}
		}
	// }
}

bool Visual_object::point_inside(const size_t par_x, const size_t par_y)
{
	if (par_x >= get_position().get_x() && par_x <= get_position().get_x() + get_width() &&
		par_y >= get_position().get_y() && par_y <= get_position().get_y() + get_height())
		return true;
	
	return false;
}

void Visual_object::move_to_end(Visual_object *child, size_t child_number)
{
	// slow_delete
	objects.extract(child_number);
	// push
	add_visual_object(child);
}

bool Visual_object::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	bool result = false;
	
	if (!point_inside(par_x, par_y))
		return result;
	
	size_t objects_amount = objects.get_length();
	
	for (long long i = (long long)objects_amount - 1; i >= 0; --i)
	{
		if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
		{
			// set_active(get_objects()->get_array()[i]);
			// (get_objects()->get_array()[i])->set_active_state(true);
			
			// // slow_delete
			// objects.extract(i);
			// // push
			// add_visual_object(get_active());
			current_active = get_objects()->get_array()[i];
			move_to_end(get_objects()->get_array()[i], i);
			
			result = true;

			// if (state)
			break;
		}

		set_active_state(false);
	}

	return result;
}

bool Visual_object::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool move = false;
	bool tmp_move = false;

	if (get_reactive() && (point_inside(from.get_x(), from.get_y()) || point_inside(to.get_x(), to.get_y())))
	{
		size_t objects_amount = objects.get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			tmp_move = (objects.get_array()[i])->on_mouse_move(from, to);
			
			if (tmp_move)
				move = tmp_move;
			// if ((objects.get_array()[i])->on_mouse_move(from, to))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			// {
			// 	// set_active(get_objects()->get_array()[i]);
			// 	// (get_objects()->get_array()[i])->set_active_state(true);
				
			// 	// slow_delete
			// 	// objects.extract(i);
			// 	// // push
			// 	// add_visual_object(get_active());
				
			// 	return true;
			// }
		}
	}

	return move;
}

bool Visual_object::on_key_pressed(const bool pressed_state, const unsigned key_mask)
{
	size_t objects_amount = objects.get_length();
	
	for (long long i = (long long)objects_amount - 1; i >= 0; --i)
	{
		if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_key_pressed(pressed_state, key_mask)) // ??????
		{
			// set_active(get_objects()->get_array()[i]);
			
			// // slow_delete
			// objects.extract(i);
			// // push
			// add_visual_object(get_active());
			current_active = get_objects()->get_array()[i];
			move_to_end(current_active, i);
			
			return true;
		}
	}

	return false;
}

bool Visual_object::on_text_entered(const char symbol)
{
	size_t objects_amount = objects.get_length();
	
	for (long long i = (long long)objects_amount - 1; i >= 0; --i)
	{
		if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_text_entered(symbol)) // ??????
		{
			current_active = get_objects()->get_array()[i];
			move_to_end(current_active, i);
			
			return true;
		}
	}

	return false;
}

void Visual_object::tick(const double delta)
{
	// assert(screen);

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (!objects_array[i]->get_alive())
		{
			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}

		objects_array[i]->tick(delta);
	}
}

void Visual_object::set_active(Visual_object *par_current_active)
{
	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	long long index = -1;

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (objects_array[i] == par_current_active)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
		return;

	current_active = par_current_active;
	current_active->set_active_state(true);

	move_to_end(par_current_active, index);
}

