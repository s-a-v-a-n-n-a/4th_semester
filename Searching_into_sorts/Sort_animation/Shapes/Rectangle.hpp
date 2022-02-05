#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

#include "../Graphical_wrapper/screen_functions.hpp" 
#include "../math_structures/Radius_vector.hpp"
#include "../math_structures/Intercepted_int.hpp"
#include "../Shape_base/Shape.hpp"

class Rectangle : public Graphical_shape 
{
private:
	Vector_ll size;

public:
	Rectangle() = delete;
	Rectangle(const double par_width, const double par_height, const char par_type, const Vector_ll &par_centre_position, const Color &par_color = WHITE);
	Rectangle(const Rectangle &other) = delete;
	// Rectangle(Rectangle &&other) = delete;
	~Rectangle() = default;

	// Radius_vector count_move(double delta_time) override;
	// void move(const Radius_vector &par_centre_position) override;

	double get_width() const { return size.get_x(); }
	double get_height() const { return size.get_y(); }
	void set_width(const double par_width) { assert(par_width >= 0); size.set_x(par_width); }
	void set_height(const double par_height) { assert(par_height >= 0); size.set_y(par_height); }

	// double get_size() const override { return get_side()/2; }
	void draw(Screen_information *screen) override;
};

#endif // RECTANGLE_CLASS
