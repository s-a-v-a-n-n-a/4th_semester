#ifndef CHART_WINDOW_HPP
#define CHART_WINDOW_HPP

#include "Window.hpp"
#include "../GUI/Chart.hpp"

class Chart_window : public Window
{
private:
    std::vector<Chart*> charts;

public:
    Chart_window(const Visual_object::Config &par_base)
    : Window(par_base, nullptr) {}

    void add_chart(Chart *chart);
    void clear();
};

#endif // CHART_WINDOW_HPP
