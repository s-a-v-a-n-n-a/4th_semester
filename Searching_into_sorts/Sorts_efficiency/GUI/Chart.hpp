#ifndef CHART_H 
#define CHART_H

#include <climits>

#include "Visual_object_base.hpp"
#include "Button.hpp"

// #include "../Editor/Graphical_delegates.hpp"

#include "../simple_list/simple_list.hpp"

extern const size_t DECREASED_DOT_SIZE;
extern const size_t DEFAULT_DOT_SIZE;

class Chart : public Visual_object
{
private:
	std::vector<Vector_ll> points;

	size_t max_x;
	size_t min_x;
	size_t max_y;
	size_t min_y;

	double x_coef;
	double y_coef;

public:
	Chart(const Visual_object::Config &par_base);
	Chart(const Visual_object::Config &par_base, std::vector<Vector_ll> dots);
	~Chart() {};

	void create_dot(const Vector_ll &point);
    
    void draw(Screen_information *screen) override;
};

#endif // CHART_H
