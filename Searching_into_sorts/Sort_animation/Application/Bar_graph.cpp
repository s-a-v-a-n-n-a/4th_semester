#include "Bar_graph.hpp"

#include "Application.hpp"

Bar_graph::Bar_graph(const Visual_object::Config &par_base, Int_container *par_reference)
: Visual_object(par_base) 
{
    size_t width = get_width();
    size_t height = get_height();

    int max_num = 0;
    int min_num = height;
    
    size_t graph_width = width / par_reference->get_length();
    Intercepted_int *array = par_reference->get_array();
    for (size_t i = 0; i < graph_width; ++i)
    {
        if (array[i].get_num() > max_num)
        {
            max_num = array[i].get_num();
        }

        if (array[i].get_num() < min_num)
        {
            min_num = array[i].get_num();
        }
    }

    double coef = (double)height / (double)(max_num - min_num);
}

void Bar_graph::change_places(size_t index1, size_t index2)
{    
    Vector_ll left_pos = elements[index1]->get_centre_position();
    Vector_ll right_pos = elements[index2]->get_centre_position();
    
    Rectangle *tmp = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = tmp;

    elements[index1]->set_centre_position(left_pos);
    elements[index2]->set_centre_position(right_pos);

    redraw();
}

void Bar_graph::redraw()
{
    Application::get_app()->graphics_wrapper->draw_rectangle(get_position(), get_width(), get_height(), get_color(), get_color());

    size_t objects_amount = elements.size();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		elements[i]->draw(Application::get_app()->graphics_wrapper);
	}
}

