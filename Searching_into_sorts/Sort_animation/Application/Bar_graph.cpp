#include "Bar_graph.hpp"

#include "Application.hpp"

Bar_graph::Bar_graph(const Visual_object::Config &par_base, Int_container *par_reference)
: Visual_object(par_base), Int_signal_receiver(), reference(par_reference) 
{
    size_t graph_width = get_width() / par_reference->get_length();
    size_t arr_len = par_reference->get_length();

    Vector_ll position = get_position();
    for (size_t i = 0; i < arr_len; ++i)
    {
        Rectangle *rect = new Rectangle(graph_width, get_height(), 1, position, FUCHSIA);
        elements.push_back(rect);

        position += Vector_ll(graph_width, 0);

        match_prototypes_indices.push_back(i);
        old_prototypes_indices.push_back(i);
    }

    synchronize();
}

void Bar_graph::synchronize()
{
    size_t width = get_width();
    size_t height = get_height();

    int max_num = -1 * height;
    int min_num = height;

    size_t graph_width = width / reference->get_length();
    size_t arr_len = reference->get_length();

    Intercepted_int *array = reference->get_array();
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

    min_num = min_num < 0 ? min_num : 0;

    double coef = (double)height / (double)(max_num - min_num + 10);
    
    for (size_t i = 0; i < arr_len; ++i)
    {
        size_t bar_height = ((double)(array[i].get_num() - min_num + 10)) * coef;
        Vector_ll position = get_position() + Vector_ll(graph_width * i, height - bar_height);
        
        elements[i]->set_height(bar_height);
        elements[i]->set_centre_position(position);

        match_prototypes_indices[i] = i;
        old_prototypes_indices[i] = i;
    }
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
        size_t lowest_id = reference->get_lowest_id();
        
        // where sender was
        size_t sender_place = match_prototypes_indices[sender.get_id() - lowest_id];
        // where other number was
        size_t others_place = match_prototypes_indices[other.get_id() - lowest_id];

        // if sender changed place but no one got his old
        if (sender_place != old_prototypes_indices[sender.get_id() - lowest_id])
        {
            // We look where sender's place was before
            sender_place = old_prototypes_indices[sender.get_id() - lowest_id];
            
            // Now sender's old place is right
            old_prototypes_indices[sender.get_id() - lowest_id] = match_prototypes_indices[sender.get_id() - lowest_id];
        }
        
        // other gets sender's place
        match_prototypes_indices[other.get_id() - lowest_id] = sender_place;
        
        // maybe someone before got other's old place
        size_t others_place_holder = 0;
        size_t elements_amount = reference->get_length();
        for (; others_place_holder < elements_amount; ++others_place_holder)
        {
            if (others_place_holder != (other.get_id() - lowest_id) && match_prototypes_indices[others_place_holder] == others_place)
            {
                /* It is like finishing the cycle of assignments 
                 * For example: 1 0 are swapping (1 goes to 0's place)
                 * First of all match_prototype_indices[1] = 0, old_prototypes_indices[1] = 1
                 * Then 0 goes to 1's place, in upper if{} old_prototypes_indices[1] = 0 
                 * then match_prototype_indices[0] = 1
                 * and now old_prototype_indeces[0] = as well, so no other number will disturb this 'cycle'
                 */
                old_prototypes_indices[other.get_id() - lowest_id] = sender_place;
                break;
            }
        }

        change_places(other.get_id() - lowest_id, sender_place);
    }
}

void Bar_graph::change_places(size_t whom, size_t where)
{    
    size_t x_pos = get_position().get_x() + where * (get_width() / reference->get_length());
    size_t y_pos = elements[whom]->get_centre_position().get_y();
    elements[whom]->set_centre_position(Vector_ll(x_pos, y_pos));

    // just delay
    for (int i = 0; i < 1000000; ++i)
        ;
    redraw();
}

void Bar_graph::draw(Screen_information *screen)
{
    screen->draw_rectangle(get_position(), get_width(), get_height(), get_color(), get_color());
    size_t objects_amount = elements.size();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		elements[i]->draw(screen);
	}
}

void Bar_graph::redraw()
{
    Application::get_app()->graphics_wrapper->draw_rectangle(get_position(), get_width(), get_height(), get_color(), get_color());

    size_t objects_amount = elements.size();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		elements[i]->draw(Application::get_app()->graphics_wrapper);
	}

    Application::get_app()->graphics_wrapper->window.display();
}

