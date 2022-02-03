#ifndef SPLINE_H 
#define SPLINE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../simple_list/simple_list.hpp"

#include "../math_structures/Interpolator.hpp"

extern const size_t DECREASED_DOT_SIZE;
extern const size_t DEFAULT_DOT_SIZE;

class Spline : public Visual_object
{
private:
	Button_delegate *delegate;

	Button *first;
	Button *last;

	std::vector<Vector_d> points;

	Vector_ll high_limit;
	Vector_ll low_limit;

public:
	Spline(const Visual_object::Config &par_base, Button_delegate *par_delegate, const Vector_ll &par_high_limit, const Vector_ll &par_low_limit);
	~Spline() { delete delegate; };

	void set_delegate(Button_delegate *par_delegate) { delegate = par_delegate; }

	Button *create_spline_dot(const Vector_ll &position, const size_t width, const size_t height);
	Interpolator *create_interpolator();

	void recount(Interpolator *interpolator);

	void add_visual_object(Visual_object *par_object) override;

	void draw(Screen_information *screen) override;

	Vector_ll create_relation(const double par_x, const double par_y);
	
	bool on_mouse_click (const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move (const Vector_ll from, const Vector_ll to) override;
	void tick(const double delta) override;

	Button_delegate *get_delegate() { return delegate; }
	void transfer_graph();
};

#endif // SPLINE_H
