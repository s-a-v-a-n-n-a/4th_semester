#include "Rectangle.hpp"

Rectangle::Rectangle(const double par_width, const double par_height, const char par_type, const Vector_ll &par_centre_position, const Color &par_color) 
: Graphical_shape(par_type, par_centre_position, par_color)
{
	assert(par_width >= EPSILON);
	assert(par_height >= EPSILON);

	size = Vector_ll(par_width, par_height);
}

void Rectangle::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_rectangle(get_centre_position(), size.get_x(), size.get_y(), get_color(), get_color());
}
