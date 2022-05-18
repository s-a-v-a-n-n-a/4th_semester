#include "Testing/Function_test.hpp"

int main()
{
    creation_test();
    assignment_test();
    lambda_test();
    lambda_with_capture_test();

    deduction_creation_test();
    deduction_assignment_test();
    deduction_lambda_test();
    deduction_lambda_with_capture_test();

    assign_test();
    target_test();

    return 0;
}