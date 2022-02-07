#include "Chart.hpp"

const size_t DECREASED_DOT_SIZE = 10;
const size_t DEFAULT_DOT_SIZE = 20;

Chart::Chart(const Visual_object::Config &par_base)
: Visual_object(par_base), points(get_width(), 0), min_x(INT_MAX), max_x(0), min_y(INT_MAX), max_y(0), x_coef(1.0), y_coef(1.0) 
{
	;
}

Chart::Chart(const Visual_object::Config &par_base, std::vector<Vector_ll> dots)
: Visual_object(par_base), points(get_width(), 0), min_x(INT_MAX), max_x(0), min_y(INT_MAX), max_y(0), x_coef(1.0), y_coef(1.0)
{
	size_t dots_amount = dots.size();

	for (size_t i = 0; i < dots_amount; ++i)
	{
		create_dot(dots[i]);
	}
}

void Chart::create_dot(const Vector_ll &point)
{
    Vector_ll new_point = Vector_ll(point);  
    points.push_back(new_point);

	if (point.get_x() < min_x)
		min_x = point.get_x();
	if (point.get_y() < min_y)
		min_y = point.get_y();
	if (point.get_x() > max_x)
		max_x = point.get_x();
	if (point.get_y() > max_y)
		max_y = point.get_y();

	x_coef = (double)get_width() / (double)max_x;
	y_coef = (double)(get_height() - DEFAULT_BUTTON_HEIGHT) / (double)max_y;

	// printf("%lld %lld\n", point.get_x() + get_position().get_x(), get_position().get_y() + get_height() - point.get_y());
}

void Chart::draw(Screen_information *screen)
{
	Vector_ll cur_pos = get_position();
	Color cur_color = get_color();

	long long cur_height = get_height();

	// x_coef = 1;
	// y_coef = 1;
	
	size_t points_amount = points.size();
	for (size_t i = 0; i < points_amount - 1; ++i)
	{
		size_t x1 = (double)((size_t)points[i].get_x()) * x_coef + cur_pos.get_x();
		size_t y1 = cur_pos.get_y() + cur_height - ((double)(size_t)points[i].get_y()) * y_coef; // DEFAULT_BUTTON_HEIGHT + 

		size_t x2 = (double)((size_t)points[i + 1].get_x()) * x_coef + cur_pos.get_x();
		size_t y2 = cur_pos.get_y() + cur_height - ((double)(size_t)points[i + 1].get_y()) * y_coef; // + DEFAULT_BUTTON_HEIGHT

		screen->draw_circle(Vector_ll(x1 - DECREASED_DOT_SIZE, y1 - DECREASED_DOT_SIZE), DECREASED_DOT_SIZE, cur_color, cur_color);
		screen->draw_line(Vector_ll(x1, y1), Vector_ll(x2, y2), cur_color);
	}

	size_t x = (double)((size_t)points[points_amount - 1].get_x()) * x_coef + cur_pos.get_x();
	size_t y = cur_pos.get_y() + cur_height - ((double)(size_t)points[points_amount - 1].get_y()) * y_coef; // + DEFAULT_BUTTON_HEIGHT	
	
	screen->draw_circle(Vector_ll(x - DECREASED_DOT_SIZE, y - DECREASED_DOT_SIZE), DECREASED_DOT_SIZE, cur_color, cur_color);
}
