#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <vector>

#include "../math_structures/Intercepted_int.hpp"
#include "../math_structures/Sorts_research.hpp"

#include "../Editor/Chart_delegates.hpp"

class DataCharts_control
{
private:
    size_t start_size;
    size_t step;
    size_t operations_amount;

    std::vector<Intercepted_int*> data;

public:
    DataCharts_control(size_t arg_start_size, size_t arg_step, size_t arg_ops_amount);
    // DataCharts_control(std::vector<Intercepted_int**> data);
    ~DataCharts_control();

    void regenerate_data();
    void conduct_research(std::vector<Vector_ll> &result, Research type, standartised_sort sort_func);
};

#endif // CONTROLLER_HPP
