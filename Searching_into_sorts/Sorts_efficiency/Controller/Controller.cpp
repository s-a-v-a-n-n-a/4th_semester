#include "Controller.hpp"

DataCharts_control::DataCharts_control(size_t arg_start_size, size_t arg_step, size_t arg_ops_amount)
: start_size(arg_start_size), step(arg_step), operations_amount(arg_ops_amount) 
{
    size_t cur_size = start_size;
    for (size_t i = 0; i < operations_amount; ++i, cur_size += step)
    {
        data.push_back(new Intercepted_int[cur_size]);
        for (size_t j = 0; j < cur_size; ++j)
        {
            data[i][j] = rand() % 1000 - 500;
        }
    }
}

DataCharts_control::~DataCharts_control()
{
    size_t data_size = data.size();
    for (long long i = data_size; i >= 0; --i)
    {
        delete [] data[i];
    }
}

void DataCharts_control::regenerate_data()
{
    size_t cur_size = start_size;
    for (size_t i = 0; i < operations_amount; ++i, cur_size += step)
    {
        for (size_t j = 0; j < cur_size; ++j)
        {
            data[i][j] = rand() % 1000 - 500;
        }
    }
}

void DataCharts_control::conduct_research(std::vector<Vector_ll> &result, Research type, standartised_sort sort_func)
{
    std::vector<Intercepted_int*> data_copy;
    size_t cur_size = start_size;
    for (size_t i = 0; i < data.size(); ++i, cur_size += step)
    {
        Intercepted_int *array = new Intercepted_int[cur_size];
        data_copy.push_back(array);
        for (size_t j = 0; j < cur_size; ++j)
            data_copy[i][j] = (data[i][j]);
    }
    
    count_sort_operations(result, data_copy, start_size, operations_amount, step, type, sort_func);

    size_t data_size = data.size();
    for (long long i = data_size - 1; i >= 0; --i)
    {
        delete [] data_copy[i];
    }
}


