#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP

#include <cstdio>
#include <iostream>

#include "../String/String.hpp"

void creation_test()
{
    printf("\nTesting string creation\n\n");
    
    String<char> string("Creation works", 14);

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

    std::cout << "REsult of creating is string: " << string << "\n";
}

void view_test()
{
    printf("\nTesting string view\n\n");
    printf("Does nothing yet\n");
    
    // char *buffer = new char[100];
    // memset(buffer, 0 , 100);
    // strncpy(buffer, "View test works\n", 17);

    // String<char> string = String<char>::view(&buffer, 100);

    // for (size_t idx = 0; idx < string.size(); ++idx)
    // {
    //     printf("%c", string[idx]);
    // }
}

void push_pop_test()
{
    printf("\nTesting string operations push and pop\n\n");
    
    String<char> string = "Hi, guys";

    char guys[] = "guys";
    size_t guys_length = strlen(guys);
    char girls[] = "girls";
    size_t girls_length = strlen(girls);

    std::cout << "Start string: " << string << "\n";

    for (size_t i = 0; i < guys_length; ++i)
    {
        string.pop_back();
    }

    std::cout << "In between result: " << string << "\n";

    for (size_t i = 0; i < girls_length; ++i)
    {
        string.push_back(girls[i]);
    }

    std::cout << "Last result: " << string << "\n";
}

void append_test()
{
    printf("\nTesting string operation += (append)\n\n");
    
    String<char> string = "Hi, dear guys";

    char guys[] = "guys";
    size_t guys_length = strlen(guys);
    char girls[] = "girls";

    std::cout << "Start string: " << string << "\n";

    for (size_t i = 0; i < guys_length; ++i)
    {
        string.pop_back();
    }

   std::cout << "In between result: " << string << "\n";

    string += girls;

    std::cout << "Last result: " << string << "\n";
}

#endif // STRING_TESTS_HPP
