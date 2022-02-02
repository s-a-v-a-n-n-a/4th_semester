#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

#include <cstdio>
#include <cstdlib>

#include "../math_structures/Radius_vector.hpp"

class Button_delegate
{
public:
	virtual ~Button_delegate() = default;

	virtual bool on_mouse_click(const size_t par_x, const size_t par_y) = 0;
	virtual bool on_mouse_release() { return false; }
	virtual bool on_mouse_move(const Vector_ll from, const Vector_ll to) { return false; }
};

#endif // BUTTON_DELEGATE
