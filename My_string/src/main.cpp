#include "Tests/string_tests.hpp"

int main()
{
    creation_test();
    sso_test();
    view_test();
    push_pop_test();
    append_test();
    copy_on_write_test();
}
