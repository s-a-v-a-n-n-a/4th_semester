#include "Chart_window.hpp"

void Chart_window::add_chart(Chart *chart)
{
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
