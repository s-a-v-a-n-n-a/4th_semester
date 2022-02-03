#ifndef RADIUS_VECTOR_CLASS
#define RADIUS_VECTOR_CLASS

#include <cmath>
#include <cstdio>

// #include "../math_structures/Matrix_4.hpp"

template <typename vector_type> class Radius_vector
{
private:
	vector_type x;
	vector_type y;
	// vector_type z;

	bool valid;

public:

	Radius_vector(vector_type par_x = (vector_type)0, vector_type par_y = (vector_type)0) // double par_z = 0.0
	{
		x = par_x;
		y = par_y;
		// z = par_z;

		valid = true;
	}
	Radius_vector(const Radius_vector& other)
	{
		x = other.x;
		y = other.y;
		// z = other.z;

		valid = true;
	}

	const Radius_vector& operator=(const Radius_vector& other) { x = other.get_x(); y = other.get_y(); return *this; } // z = other.get_z(); 

	const Radius_vector& operator+=(const Radius_vector &other) { x += other.get_x(); y += other.get_y(); return *this; } // z += other.get_z();
	const Radius_vector& operator-=(const Radius_vector &other) { x -= other.get_x(); y -= other.get_y(); return *this; } // z -= other.get_z(); 
	const Radius_vector& operator*=(const double scale) { x = (double)x * scale; y = (double)y * scale; return *this; } // z *= scale;
	const Radius_vector& operator/=(const double scale) 
	{ 
		if (scale == 0) 
		{
			valid = false;
			return *this; 
		}

		x /= scale; y /= scale; // z /= scale; 
		return *this; 
	} 
	
	const Radius_vector operator+(const Radius_vector &other) const { return { x + other.get_x(), y + other.get_y() }; } // z + other.get_z() 
	const Radius_vector operator-(const Radius_vector &other) const { return { x - other.get_x(), y - other.get_y() }; } // z - other.get_z()
	const Radius_vector operator*(const double scale) const { return { (vector_type)((double)x * scale), (vector_type)((double)y * scale) }; } // z * scale
	const Radius_vector operator/(const double scale) const 
	{
		if (scale == 0) 
		{
			return Radius_vector(*this); 
		}

		return { (vector_type)((double)x / scale), (vector_type)((double)y / scale) };
	}

	bool operator==(const Radius_vector &other) const { if (x == other.x && y == other.y) return true; return false; }
	bool operator!=(const Radius_vector &other) const { if (x != other.x || y != other.y) return true; return false; }
	
	void componentwise_multiplication(const Radius_vector &other)
	{ 
		x *= other.get_x();
		y *= other.get_y();
		// z *= other.get_z();
	}

	const double scalar_multiplication(const Radius_vector &other) const
	{
		return x * other.get_x() + y * other.get_y(); // + z * other.get_z()
	}

	const double length() const
	{
		return sqrt(x * x + y * y); // + z * z
	}

	vector_type get_x() const { return x; }
	vector_type get_y() const { return y; }
	// double get_z() const { return z; }

	void set_x(vector_type par_x) { x = par_x; }
	void set_y(vector_type par_y) { y = par_y; }
	// void set_z(double par_z) { z = par_z; }

	Radius_vector reflect_vector(const Radius_vector& normal)
	{
		Radius_vector tmp_normal(normal);
		Radius_vector tmp_vector(*this);

		tmp_normal /= tmp_normal.length();
		double projection = tmp_vector.scalar_multiplication(tmp_normal) * 2.0;
		if (projection < 0)
			projection *= -1;

		tmp_normal *= projection;
		tmp_vector += tmp_normal;

		return tmp_vector;
	}
	// Radius_vector mul_vector_and_matrix4 (const Matrix_4 &matrix) const;
	void rotate_point (const Radius_vector &other, const double par_angle)
	{
		Radius_vector horizontal(1, 0);
		Radius_vector vertical(0, -1);
		Radius_vector relative(*this);
		relative -= other;

		double length = relative.length();

		Radius_vector hor_projection = relative.get_projection(horizontal);
		Radius_vector ver_projection = relative.get_projection(vertical);

		Radius_vector this_parallel(relative);
		this_parallel /= length;
		Radius_vector this_normal(this_parallel.normal());

		this_normal *= length * sin(par_angle);
		this_parallel *= length * (1 - cos(par_angle));

		*this -= this_parallel + this_normal;
	}

	void normalization() { *this /= length(); }
	const Radius_vector normal() const { return Radius_vector(-1 * y, x); } 
	const double get_angle(const Radius_vector &other) 
	{ 
		double scalar = scalar_multiplication(other)/(length() * other.length());
		return acos(scalar);
	}
	const double get_cos_angle(const Radius_vector &other) { return scalar_multiplication(other)/(length() * other.length()); }
	const double get_projection(const Radius_vector &other) { if (!length()) return 0; return scalar_multiplication(other)/length(); }
};

typedef Radius_vector<long long> Vector_ll;
typedef Radius_vector<double> Vector_d;

#endif // RADIUS_VECTOR_CLASS
