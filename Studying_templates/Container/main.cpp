#include "src/Trainings/Static_mem_tests.hpp"
#include "src/Trainings/Dynamic_mem_tests.hpp"
#include "src/Trainings/Chunked_mem_tests.hpp"

int main()
{
    // Trainings::static_test::for_int();
    Trainings::dynamic_test::test_no_construct();

    // Trainings::chunked_test::for_bool(); 
    
    return 0;
}
