#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP

#include <cstdio>

#include "../String/String.hpp"

void creation_test()
{
    printf("\nTesting string creation\n\n");
    
    String<char> string("Creation works", 15);

    for (size_t idx = 0; idx < string.size(); ++idx)
    {
        printf("%c", string[idx]);
    }
    printf("\n");
}

void sso_test()
{
    printf("\nTesting string sso\n\n");
    
    String<char> string("SSO", 4);

    for (size_t idx = 0; idx < string.size(); ++idx)
    {
        printf("%c", string[idx]);
    }
    printf("\n");
}

void view_test()
{
    printf("\nTesting string view\n\n");
    
    char *buffer = new char[100];
    memset(buffer, 0 , 100);
    strncpy(buffer, "View test works\n", 17);

    String<char> string = String<char>::view(&buffer, 100);

    for (size_t idx = 0; idx < string.size(); ++idx)
    {
        printf("%c", string[idx]);
    }
}

#endif // STRING_TESTS_HPP
