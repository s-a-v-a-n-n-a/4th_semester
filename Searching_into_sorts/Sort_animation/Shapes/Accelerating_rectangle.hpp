#ifndef ACCELERATING_RECTANGLE_CLASS
#define ACCELERATING_RECTANGLE_CLASS

#include "../sfml_drawing/screen_functions.hpp"
#include "../math_structures/Radius_vector.hpp"
#include "../Shape_base/Shape.hpp"
#include "Rectangle.hpp"

class Accelerating_rectangle : public Rectangle 
{
private:
	Radius_vector acceleration;

public:
	Accelerating_rectangle(const Radius_vector &par_acceleration, const double par_width, const double par_height, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color = WHITE);
	Accelerating_rectangle(const Accelerating_rectangle &other) = delete;
	~Accelerating_rectangle() = default;

	Radius_vector count_move(const double delta_time) override;
	void move(const Radius_vector &par_centre_position) override;
};

#endif // ACCELERATING_RECTANGLE_CLASS
