#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS

const double EPSILON = 0.000001;

inline double cosine_scalar(double scalar, double length_1, double length_2)
{
	if (!length_1 || !length_2)
		return 0;

	return scalar/(length_1 * length_2);
}

inline double calculate_power(double value, int power)
{
	if (power == 0)
		return 1.0;

	double answer = 1.0;
	double multiplier = value;

	while (power)
	{
		if (power & 1)
			answer = (answer * multiplier);
		multiplier *= multiplier;
		power >>= 1;
	}

	return answer;
}

inline bool is_inside_triangle(const Vector_ll &p, const Vector_ll &p1, const Vector_ll &p2, const Vector_ll &p3)
{
	double cross1 = (p1.get_x() - p.get_x()) * (p2.get_y() - p1.get_y()) - (p2.get_x() - p1.get_x()) * (p1.get_y() - p.get_y());
	double cross2 = (p2.get_x() - p.get_x()) * (p3.get_y() - p2.get_y()) - (p3.get_x() - p2.get_x()) * (p2.get_y() - p.get_y());
	double cross3 = (p3.get_x() - p.get_x()) * (p1.get_y() - p3.get_y()) - (p1.get_x() - p3.get_x()) * (p3.get_y() - p.get_y());

	if (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 || cross1 >= 0 && cross2 >= 0 && cross3 >= 0)
		return true;
	else
		return false;
}


#endif // MATH_FUNCTIONS
