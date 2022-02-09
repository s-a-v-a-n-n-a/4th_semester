#ifndef SHAPE_CLASS
#define SHAPE_CLASS

#include <assert.h>

#include "../Graphical_wrapper/screen_functions.hpp"
#include "../math_structures/Radius_vector.hpp"
#include "../math_structures/math_functions.hpp"

class Graphical_shape
{
private:
	const char type;

	Vector_ll centre_position;

	Color color;
public:
	Graphical_shape() = delete;
	Graphical_shape(const char par_type);
	Graphical_shape(const char par_type, const Vector_ll &par_centre_position, const Color &par_color = WHITE);
	~Graphical_shape() {}

	char get_type() const { return type; }
	Vector_ll get_centre_position() const { return centre_position; }
	Color get_color() const { return color; }

	void set_centre_position(const Vector_ll &par_centre_position) { centre_position = par_centre_position; }
	void set_color(const Color par_color) { color = par_color; }

	// virtual double get_size() const { return 0.0; }
	virtual void draw(Screen_information *screen) { ; }
};

#endif // SHAPE_CLASS
