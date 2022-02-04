#ifndef INT_ARRAY_DELEGATES_HPP
#define INT_ARRAY_DELEGATES_HPP

#include "../GUI/Button_delegate.hpp"

#include "../math_structures/Sorts.hpp"
#include "../math_structures/Int_container.hpp"
class Sort_delegate : public Button_delegate
{
private:
    Int_container *array_container;
    void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *));
	
public:
    Sort_delegate(Int_container *arg_container, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)));

    bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

#endif // INT_ARRAY_DELEGATES_HPP
