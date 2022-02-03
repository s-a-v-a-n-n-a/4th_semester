#include "Shape.hpp"

Graphical_shape::Graphical_shape(const char par_type) 
: type(par_type), centre_position({0, 0}) {}

Graphical_shape::Graphical_shape(const char par_type, const Vector_ll &par_centre_position, const Color &par_color)
: type(par_type), centre_position(par_centre_position), color(par_color) {}
