#ifndef CHART_WINDOW_HPP
#define CHART_WINDOW_HPP

#include "Window.hpp"
#include "../GUI/Chart.hpp"

class Chart_window : public Window
{
private:
    std::vector<Chart*> charts;

public:
    Chart_window(const Visual_object::Config &par_base, const char *name = nullptr)
    : Window(par_base, name) {}

    void add_chart(Chart *chart);
    void clear();
};

#endif // CHART_WINDOW_HPP
