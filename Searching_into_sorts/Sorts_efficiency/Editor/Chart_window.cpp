#include "Chart_window.hpp"

void Chart_window::add_chart(Chart *chart)
{
    double new_x_coef = chart->get_x_coef();
    double new_y_coef = chart->get_y_coef();
    
    size_t charts_amount = charts.size();
    for (size_t i = 0; i < charts_amount; ++i)
    {
        if (new_x_coef < charts[i]->get_x_coef())
        {
            charts[i]->set_x_coef(new_x_coef);
        }
        else
        {
            chart->set_x_coef(charts[i]->get_x_coef());
            new_x_coef = chart->get_x_coef();;
        }

        if (new_y_coef < charts[i]->get_y_coef())
        {
            charts[i]->set_y_coef(new_y_coef);
        }
        else
        {
            chart->set_y_coef(charts[i]->get_y_coef());
            new_y_coef = chart->get_y_coef();
        }
    }

    charts.push_back(chart);
    add_visual_object(chart);
}

void Chart_window::clear()
{
    size_t charts_amount = charts.size();

    for (long long i = charts_amount - 1; i >= 0; --i)
    {
        very_slow_delete_visual_object(charts[i]);
        // delete charts[i];
        charts.pop_back();
    }
}
