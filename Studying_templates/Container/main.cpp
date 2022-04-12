#include "src/Trainings/Static_mem_tests.hpp"
#include "src/Trainings/Dynamic_mem_tests.hpp"
#include "src/Trainings/Chunked_mem_tests.hpp"

int main()
{
    // Trainings::static_test::for_std_find();
    // Trainings::static_test::for_std_copy();
    // Trainings::dynamic_test::for_range_based_for();

    // Trainings::chunked_test::for_iterator(); 
    Trainings::dynamic_test::for_reversed_iterator(); 
    // Trainings::chunked_test::for_std_find(); 
    // Trainings::chunked_test::for_std_copy(); 

    return 0;
}
