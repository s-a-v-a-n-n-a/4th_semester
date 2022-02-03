#ifndef DRAWING
#define DRAWING

#include <SFML/Graphics.hpp>
#include <cmath>

enum Shapes_types
{
	POINT = 1,
	LINE  = 2
};

class Point
{
public:
	double x;
	double y;

	const Point operator+=(const Point &other) { return { x += other.x, y += other.y }; } 
	const Point operator-=(const Point &other) { return { x -= other.x, y -= other.y }; } 
	const Point operator*=(const double scale) { return { x *= scale, y *= scale }; } 
};

// class Point_3d
// {
// public:
// 	double x;
// 	double y;
// 	double z;

// 	Point_3d& operator+=(const Point_3d &other) { x += other.x; y += other.y; z += other.z; return *this;/*return { x + other.x, y + other.y, z + other.z };*/ } 
// 	Point_3d& operator-=(const Point_3d &other) { x -= other.x; y -= other.y; z -= other.z; return *this;/*return { x - other.x, y - other.y, z - other.z };*/ } 
// 	Point_3d& operator*=(const double scale) { x *= scale; y *= scale; z *= scale; return *this;/*return { x * scale, y * scale, z * scale }; */} 

// 	// friend Point_3d operator+(Point_3d this_one, const Point_3d &other) { this_one += other; return this_one; }
// 	// friend Point_3d operator-(Point_3d this_one, const Point_3d &other) { this_one -= other; return this_one; }

// 	Point section_along_z() { return { x, y }; }

// 	//в плоскости xy
// 	Point_3d rotate_point_on_flat(Point_3d point_0, double angle)
// 	{
// 		return { point_0.x + (x - point_0.x) * cos(angle) - (y - point_0.y) * sin(angle),
// 				 point_0.y + (x - point_0.x) * sin(angle) + (y - point_0.y) * cos(angle),
// 				 z };
// 	}
// };

inline void draw_point_sfml(sf::RenderWindow *window, Point point)
{
	sf::Vertex sfml_point(sf::Vector2f(point.x, point.y), sf::Color(196, 0, 171));

	window->draw(&sfml_point, POINT, sf::Points);
}

inline void draw_line_sfml(sf::RenderWindow *window, Point begin, Point end) // redo // redid
{
	sf::Vertex sfml_begin(sf::Vector2f(begin.x, begin.y), sf::Color(196, 0, 171));
	sf::Vertex sfml_end(sf::Vector2f(end.x, end.y), sf::Color(196, 0, 171));

	sf::Vertex line[] = { sfml_begin, sfml_end };
	window->draw(line, LINE, sf::Lines); // magic // where
}

inline void draw_circle_sfml(sf::RenderWindow *window, Point position, double radius)
{
	sf::CircleShape circle(radius);
	circle.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
	circle.setFillColor(sf::Color::Black);
	
	window->draw(circle);
}

#endif // DRAWING
