#ifndef MOLECULA_CLASS
#define MOLECULA_CLASS

#include "../sfml_drawing/screen_functions.hpp"
#include "../math_structures/Radius_vector.hpp"
#include "../Shape_base/Shape.hpp"

class Molecula : public Shape
{
private:
	double radius;

public:
	Molecula() = delete;
	Molecula(const double par_radius, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color = WHITE);
	Molecula(const Molecula &other) = delete;
	// Molecula(Molecula &&other) = delete;
	~Molecula() = default;

	Radius_vector count_move(double delta_time) override;
	void move(const Radius_vector &par_centre_position) override;

	double get_radius() const { return radius; }
	void set_radius(const double par_radius) { assert(par_radius >= 0); radius = par_radius; }

	void draw(Screen_information *screen) override;
};

#endif // MOLECULA_CLASS
