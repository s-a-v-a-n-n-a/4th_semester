#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <new>

#include "String_core.hpp"

#define SIZE_T_HIGH_BIT(number) (number >> sizeof(size_t))  

template <typename CharType> // strategy
class String : protected String_core<CharType>
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String() 
    : String_core()
    {}

    constexpr String(const CharType *string, size_t count)
    : String_core(string, count)
    {}

    /**
     * Unsafe if 
     * a) string is NOT null-terminated;
     * b) sizeof(CharType) != 1;
     * It will be NOT safe if null can be reached in other way than last symbol
     */
    constexpr String(const CharType *string)
    : String_core(string, strlen(string))
    {}

    constexpr explicit String(const String &other)
    : String_core(other)
    {}

    constexpr String(const String &other, size_t position)
    : String_core(other, position)
    {}

    constexpr String(const String &other, size_t position, size_t count)
    : String_core(other, position, count)
    {}

    constexpr String(size_t count, CharType value)
    : String_core(count, value)
    {}

    static String view(CharType **buffer, size_t count)
    {
        return (String)String_core::view(buffer, count);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity       ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using String_core::size;
    using String_core::capacity;

    bool empty()
    {
        return size() == 0;
    }

    [[nodiscard]] size_t length()
    {
        return size();
    }

    using String_core::shrink_to_fit;
    using String_core::reserve;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Element access ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr CharType &at(size_t position)
    {
        return (*this)[position];
    }

    CharType &operator[](size_t index)
    {
        return data(index);
    }

    const CharType &operator[](size_t index) const
    {
        return const_cast((this)[index]);
    }

    constexpr CharType &front()
    {
        return (*this)[0];
    }
    
    constexpr CharType &back()
    {
        return (*this)[size() - 1];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operations     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using String_core::resize;

    constexpr void push_back(CharType value)
    {
        if (size() + 1 > max_size())
        {
            throw std::length_error("Too big string\n");
        }

        if (size() > capacity())
        {
            reserve(capacity() * 2);
        }

        data(size()) = value;
        ++size_;
    }

    constexpr void pop_back(CharType value)
    {
        if (empty())
        {
            throw std::out_of_range("Wrong index range\n");
        }

        --size_;
        if (size() < capacity() / 4)
        {
            resize(capacity() / 2);
        }
    }
};

#endif // MY_STRING_HPP
