#include "Chart_delegates.hpp"
#include "Application.hpp"
#include "../Controller/Controller.hpp"

Generate_chart::Generate_chart(Chart_window *arg_field, const Color &arg_color, Research arg_type, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)))
: Button_delegate(), field(arg_field), color(arg_color), sort(arg_sort), type(arg_type)
{}

bool Generate_chart::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Generate_chart::on_mouse_release()
{
    std::vector<Vector_ll> result;
    // count_sort_operations(result, 5, 15, 100, type, sort); // start array length, amount, step
    
    Application::get_app()->get_controller()->conduct_research(result, type, sort);

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

Regenerate_data::Regenerate_data()
: Button_delegate() {}

bool Regenerate_data::on_mouse_click(const size_t par_x, const size_t par_y)
{
    return true;
}

bool Regenerate_data::on_mouse_release()
{
    Application::get_app()->get_controller()->regenerate_data();

    return true;
}
