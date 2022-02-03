#include "Chart_delegates.hpp"

Generate_chart::Generate_chart(Chart_window *arg_field, const Color &arg_color, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
: Button_delegate(), field(arg_field), color(arg_color), sort(arg_sort)
{}

bool Generate_chart::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Generate_chart::on_mouse_release()
{
    std::vector<Vector_ll> result;
    count_sort_operations(result, 5, 10, 5, sort); // start array length, amount, step
    for (int i = 0; i < 10; i++)
    {
       printf("%lld:%lld ", result[i].get_x(), result[i].get_y());
    }
    printf("\n");

    Chart *new_chart = new Chart({field, (size_t)Vidget_type::CHART, field->get_position(), nullptr, color, field->get_width(), field->get_height()}, result);
    field->add_chart(new_chart);

    return true;
}

Clear_field::Clear_field(Chart_window *arg_field)
: Button_delegate(), field(arg_field) {}

bool Clear_field::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Clear_field::on_mouse_release()
{
    field->clear();

    return true;
}

