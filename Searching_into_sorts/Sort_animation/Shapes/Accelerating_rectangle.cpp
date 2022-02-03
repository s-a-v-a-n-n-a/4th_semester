#include "Accelerating_rectangle.hpp"

Accelerating_rectangle::Accelerating_rectangle(const Radius_vector &par_acceleration, const double par_width, const double par_height, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color) : Rectangle(par_width, par_height, par_type, par_centre_position, par_velocity, par_weight, par_color)
{
	acceleration = par_acceleration;
}

Radius_vector Accelerating_rectangle::count_move(const double delta_time)
{
	Radius_vector result(get_centre_position() + get_velocity() * delta_time + acceleration * delta_time * delta_time / 2.0);
	set_velocity(acceleration * delta_time + get_velocity());

	return result;
	// return Radius_vector(get_centre_position() + get_velocity() * delta_time);
}

void Accelerating_rectangle::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position); // неверная формула
}
