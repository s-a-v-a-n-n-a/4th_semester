#include "Molecula.hpp"

Molecula::Molecula(const double par_radius, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color) : Shape(par_type, par_centre_position, par_velocity, par_weight, par_color)
{
	assert(radius >= 0);

	radius = par_radius;
}

Radius_vector Molecula::count_move(const double delta_time)
{
	return Radius_vector(get_centre_position() + get_velocity() * delta_time);
}

void Molecula::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position);
}

void Molecula::draw(Screen_information *screen)
{
	assert(screen);

	size_t width  = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			double x0 = get_centre_position().get_x();
			double y0 = get_centre_position().get_y();
			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < radius * radius)
			{
				screen->set_color(y, x, get_color());
			}
		}
	}
}
