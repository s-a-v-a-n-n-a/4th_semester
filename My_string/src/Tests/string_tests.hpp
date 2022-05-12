#ifndef STRING_TESTS_HPP
#define STRING_TESTS_HPP

#include <cstdio>
#include <iostream>

#include "../String/String.hpp"
#include "../Allocators/Allocator.hpp"

using Char_string = String<char, Zeroing_allocator>;

void creation_test()
{
    printf("\nTesting string creation\n\n");
    
    Char_string string("Creation works", 14);

    std::cout << string << "\n";
}

void sso_test()
{
    printf("\nTesting string sso\n\n");
    
    Char_string string("SSO", 4);

    std::cout << "Result of creating is string: " << string << "\n";
}

void view_test()
{
    printf("\nTesting string improvement: view\n\n");
    
    char *buffer = new char[100];
    memset(buffer, 0 , 100);
    strncpy(buffer, "View test works", 16);

    Char_string string = Char_string::view(&buffer, 100);

    std::cout << "String size: " << string.size() << ", string itself: \"" << string << "\"\n";
}

void push_pop_test()
{
    printf("\nTesting string operations push and pop\n\n");
    
    Char_string string = "Hi, guys";

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
    
    Char_string string = "Hi, dear guys";

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

void copy_on_write_test()
{
    printf("\nTesting string improvement: copy-on-write\n\n");

    Char_string first_string = "Common buffer is very very big";
    Char_string second_string(first_string);
    Char_string third_string(first_string);

    first_string[1] = 'a';

    std::cout << "1) " << first_string << " \n2) " << second_string << " \n3) " << third_string << "\n"; 
}

void comparison_test()
{
    Char_string less = "less";
    Char_string more = "more";

    if (less == more)
        std::cout << "String \"" << less << "\" is equal to \"" << more << "\".\n";
    else
        std::cout << "String \"" << less << "\" is not equal to \"" << more << "\".\n";

    Char_string greater = "greater";

    if (less < greater)
        std::cout << "String \"" << less << "\" is less than \"" << greater << "\".\n";
    else
        std::cout << "String \"" << less << "\" is greater than \"" << greater << "\".\n";

}

#endif // STRING_TESTS_HPP
