#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <cmath>
#include <cassert>

#include "Radius_vector.hpp"

const double DELTA = 20;

void merging_length(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin);
void merge_sort(std::vector<Vector_d> &arr, long long sz_arr, long long index_to_begin, void merging(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin));

class Interpolator
{
private:
	std::vector<Vector_d> reference_points;
public:
	Interpolator(const std::vector<Vector_d> &par_reference_points)
	{
		size_t points_amount = par_reference_points.size();
		for (size_t i = 0; i < points_amount; ++i)
		{
			reference_points.push_back(par_reference_points[i]);
		}

		merge_sort(reference_points, points_amount, 0, merging_length);

		// printf("points amount %lu\n", points_amount);
	}

	void add_point(const Vector_d &par_point)
	{
		// resort
		// printf("add\n");

		reference_points.push_back(par_point);
		size_t points_amount = reference_points.size();
		
		// Vector_d tmp_point = par_point;
		// Vector_d point = par_point;

		// size_t index_to_insert = 0;
		// for (size_t i = 0; i < points_amount - 1; ++i)
		// {
		// 	if (point.get_x() >= reference_points[i].get_x() && point.get_x() <= reference_points[i + 1].get_x())
		// 	{
		// 		index_to_insert = i + 1;
		// 		break;
		// 	}
			
		// 	index_to_insert++;
		// }

		// for (size_t i = index_to_insert; i < points_amount; ++i)
		// {
		// 	point = tmp_point;
		// 	tmp_point = reference_points[i];
			
		// 	reference_points[i] = point;
		// }
		merge_sort(reference_points, points_amount, 0, merging_length);
		
	}

	double get_t(const Vector_d &point_0, const Vector_d &point_1, double t, double alpha) 
	{
	    Vector_d d = point_1 - point_0;
	    double a = d.scalar_multiplication(d);
	    double b = std::pow(a, alpha * 0.5);
	    return (b + t);
	}

	double linear_interpolation(double a, double b, double t)
	{
		if (t >= 0 && t <= 1)
			return a + (b - a) * t;
		else if (t < 0)
			return a;
		else
			return b;
	}

	// code from wikipedia
	Vector_d interpolation(const Vector_d &point_0, const Vector_d &point_1, const Vector_d &point_2, const Vector_d &point_3, double t, double alpha)
	{
		// printf("0: %lg, %lg; 1: %lg, %lg; 2: %lg, %lg; 3: %lg, %lg\n", point_0.get_x(), point_0.get_y(), point_1.get_x(), point_1.get_y(), point_2.get_x(), point_2.get_y(), point_3.get_x(), point_3.get_y());

		double t1 = 0.0;
		assert(point_0 != point_1);
	    double t2 = get_t(point_0, point_1, t1, alpha);
		assert(point_1 != point_2);
	    double t3 = get_t(point_1, point_2, t2, alpha);
		assert(point_2 != point_3);
	    double t4 = get_t(point_2, point_3, t3, alpha);

	    t = linear_interpolation(t2, t3, t);
	    // assert(t2 != t1);
	    // assert(t3 != t2);
	    // assert(t4 != t);
	    // assert(t4 != t3);
	    Vector_d A1 = point_0 * ((t2 - t) / (t2 - t1)) + point_1 * ((t - t1) / (t2 - t1));
	    Vector_d A2 = point_1 * ((t3 - t) / (t3 - t2)) + point_2 * ((t - t2) / (t3 - t2));
	    Vector_d A3 = point_2 * ((t4 - t) / (t4 - t3)) + point_3 * ((t - t3) / (t4 - t3));

	    Vector_d B1 = A1 * ((t3 - t) / (t3 - t1)) + A2 * ((t - t1) / (t3 - t1));
	    Vector_d B2 = A2 * ((t4 - t) / (t4 - t2)) + A3 * ((t - t2) / (t4 - t2));
	    
	    assert(t3 != t2);
	    Vector_d C  = B1 * ((t3 - t) / (t3 - t2)) + B2 * ((t - t2) / (t3 - t2));
	    
	    // assert(!std::isnan(C.get_y()));

	    return C;
	}
	

	Vector_d get_point(double x, size_t *last_ref_point)
	{
		while (*last_ref_point + 1 < reference_points.size() && x > reference_points[*last_ref_point + 1].get_x())
		{
			(*last_ref_point)++;
		}
		
		if (*last_ref_point == 0)
		{
			Vector_d point_0 = Vector_d(reference_points[0].get_x() - DELTA, reference_points[0].get_y() + DELTA);
			
			Vector_d point_1 = Vector_d(reference_points[0].get_x(), reference_points[0].get_y());
			Vector_d point_2 = Vector_d(reference_points[1].get_x(), reference_points[1].get_y());

			Vector_d point_3 = point_2;

			if (reference_points.size() <= 2)
			{
				point_3 = Vector_d(reference_points[1].get_x() + DELTA, reference_points[1].get_y() - DELTA);
			}
			else
				point_3 = Vector_d(reference_points[*last_ref_point + 2].get_x(), reference_points[*last_ref_point + 2].get_y());

			// printf("1\n");
			return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);
		}
		
		if (*last_ref_point == reference_points.size() - 2)
		{
			Vector_d point_1 = Vector_d(reference_points[*last_ref_point].get_x(), reference_points[*last_ref_point].get_y());
			Vector_d point_2 = Vector_d(reference_points[*last_ref_point + 1].get_x(), reference_points[*last_ref_point + 1].get_y());

			Vector_d point_3 = Vector_d(reference_points[*last_ref_point + 1].get_x(), reference_points[*last_ref_point + 1].get_y() + DELTA);
			
			Vector_d point_0 = point_1;

			if (reference_points.size() <= 2)
			{
				point_0 = Vector_d(reference_points[0].get_x() - DELTA, reference_points[0].get_y());
			}
			else
				point_0 = Vector_d(reference_points[*last_ref_point - 1].get_x(), reference_points[*last_ref_point - 1].get_y());

			// printf("2\n");
			return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);

		}

		Vector_d point_0 = reference_points[(*last_ref_point) - 1]; 

		Vector_d point_1 = reference_points[(*last_ref_point)]; 
		Vector_d point_2 = reference_points[(*last_ref_point) + 1];
		
		Vector_d point_3 = reference_points[(*last_ref_point) + 2];

		Vector_d closest = point_1 - point_0;

		// printf("3, point_2 %lg, point_3 %lg\n", point_2.get_x(), point_3.get_x());
		return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);
	}
};

#endif // INTERPOLATOR_H
