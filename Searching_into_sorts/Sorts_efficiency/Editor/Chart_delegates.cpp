#include "Chart_delegates.hpp"
#include "Application.hpp"
#include "../Controller/Controller.hpp"

// Generate chart delegate
// ----------------------------------------------------------------------------------------------------------------

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
    
    Application::get_app()->get_controller()->conduct_research(result, type, sort);

    Chart *new_chart = new Chart({field, (size_t)Vidget_type::CHART, field->get_position(), nullptr, color, field->get_width(), field->get_height()}, result);
    field->add_chart(new_chart);

    return true;
}

// ---------------------------------------------------------------------------------------------------------------
// Animating generate chart delegate
// ---------------------------------------------------------------------------------------------------------------

Animating_generate_graph::Animating_generate_graph(Chart_window *arg_field, const Color &arg_color, Research arg_type, void (*arg_sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)), Visual_object *par_to_animate)
: Generate_chart(arg_field, arg_color, arg_type, arg_sort), Animating(par_to_animate) {}

bool Animating_generate_graph::on_mouse_click(const size_t par_x, const size_t par_y)
{
    Generate_chart::on_mouse_click(par_x, par_y);
    return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_generate_graph::on_mouse_release()
{
    return Generate_chart::on_mouse_release();
}

bool Animating_generate_graph::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
    return Animating::on_mouse_move(from, to);
}

// ---------------------------------------------------------------------------------------------------------------

// Clear field delegate
// ---------------------------------------------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------------------------------------------
// Animating clear field delegate
// ---------------------------------------------------------------------------------------------------------------

Animating_clear_field::Animating_clear_field(Chart_window *arg_field, Visual_object *par_to_animate)
: Clear_field(arg_field), Animating(par_to_animate) {}

bool Animating_clear_field::on_mouse_click(const size_t par_x, const size_t par_y)
{
    Clear_field::on_mouse_click(par_x, par_y);
    return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_clear_field::on_mouse_release()
{
    return Clear_field::on_mouse_release();
}

bool Animating_clear_field::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
    return Animating::on_mouse_move(from, to);
}

// ---------------------------------------------------------------------------------------------------------------
// Regenerate graph delegate
// ---------------------------------------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------------------------------------
// Animating regenerating data
// --------------------------------------------------------------------------------------------------------------

Animating_regenerate_data::Animating_regenerate_data(Visual_object *par_to_animate)
: Regenerate_data(), Animating(par_to_animate) {}

bool Animating_regenerate_data::on_mouse_click(const size_t par_x, const size_t par_y)
{
    Regenerate_data::on_mouse_click(par_x, par_y);
    return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_regenerate_data::on_mouse_release()
{
    return Regenerate_data::on_mouse_release();
}

bool Animating_regenerate_data::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
    return Animating::on_mouse_move(from, to);
}

// --------------------------------------------------------------------------------------------------------------
