#include "Bar_graph.hpp"

#include "Application.hpp"

Bar_graph::Bar_graph(const Visual_object::Config &par_base, Int_container *par_reference)
: Visual_object(par_base), Int_signal_receiver(), reference(par_reference) 
{
    size_t width = get_width();
    size_t height = get_height();

    int max_num = -1 * height;
    int min_num = height;
    
    size_t graph_width = width / par_reference->get_length();
    size_t arr_len = par_reference->get_length();
    printf("container length %llu\n", arr_len);

    Intercepted_int *array = par_reference->get_array();
    for (size_t i = 0; i < arr_len; ++i)
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

    double coef = (double)height / (double)(max_num - min_num + 10);
    printf("coef %lg, %d, %d\n", coef, max_num, min_num);

    for (size_t i = 0; i < arr_len; ++i)
    {
        size_t bar_height = ((double)(array[i].get_num() - min_num + 10)) * coef;
        printf("%zu:%d ", bar_height, array[i].get_num() - min_num + 10);
        Vector_ll position = get_position() + Vector_ll(graph_width * i, height - bar_height);
        Rectangle *rect = new Rectangle(graph_width, bar_height, 1, position, FUCHSIA);

        elements.push_back(rect);
    }
    printf("\n");
}

Bar_graph::~Bar_graph()
{
    size_t elements_amount = elements.size();

    for (long long i = elements_amount - 1; i >= 0; --i)
    {
        delete elements[i];
        elements.pop_back();
    }   
}

void Bar_graph::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    if (signal_type == Int_signal::ASSIGN)
    {
        printf("%lld\n", (&sender - (const Intercepted_int*)reference) / sizeof(const Intercepted_int));
        change_places((&sender - (const Intercepted_int*)reference) / sizeof(const Intercepted_int), (&other - (const Intercepted_int*)reference) / sizeof(const Intercepted_int));
    }
}

void Bar_graph::change_places(size_t index1, size_t index2)
{    
    printf("bars amount %zu, %lld:%lld\n", elements.size(), index1, index2);

    Vector_ll left_pos = elements[index1]->get_centre_position();
    Vector_ll right_pos = elements[index2]->get_centre_position();
    
    Rectangle *tmp = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = tmp;

    elements[index1]->set_centre_position(left_pos);
    elements[index2]->set_centre_position(right_pos);

    redraw();
}

void Bar_graph::draw(Screen_information *screen)
{
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

