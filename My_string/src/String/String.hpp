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
private:
    typedef String_core<CharType> String_core;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr explicit String(const String_core &core)
    : String_core(core)
    {}

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

    constexpr explicit String(String &other)
    : String_core(other)
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
        return String<CharType>(String_core::view(buffer, count));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operator =     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String &operator=(const String &other)
    {
        String_core::operator=(other);

        return *this;
    }

    constexpr String &operator=(const String &&other)
    {
        String_core::operator=(other);

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity       ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using String_core::size;
    using String_core::capacity;
    using String_core::max_size;

    bool empty() const
    {
        return size() == 0;
    }

    [[nodiscard]] size_t length() const
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
        return String_core::data(index);
    }

    const CharType &operator[](size_t index) const
    {
        return const_cast<CharType&>((this)[index]);
    }

    constexpr CharType &front()
    {
        return (*this)[0];
    }
    
    constexpr CharType &back()
    {
        return (*this)[size() - 1];
    }

    using String_core::c_str;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operations     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using String_core::resize;

    constexpr void push_back(CharType value)
    {
        if (size() + 1 > max_size())
        {
            throw std::length_error("Too big required size in push_back\n");
        }

        String_core::expand(value);
    }

    constexpr void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("Wrong index range in pop_back\n");
        }

        String_core::shrink();
    }

    constexpr String &append(size_t count, CharType value)
    {
        reserve(size() + count);
        
        for (size_t idx = 0; idx < count; ++idx)
        {
            push_back(value);
        }

        return *this;
    }

    constexpr String &append(const String& string, size_t position = 0, size_t count = 0)
    {
        if (count == 0)
        {
            count = string.size() - position;
        }
        
        if (position > string.size())
        {
            throw std::out_of_range("Too big required size in append\n");
        }
        
        return append(string.no_null_data(), count, position);
    }

    constexpr String& append(const CharType* string, size_t count, size_t position = 0)
    {
        reserve(size() + count);

        for (size_t idx = position; idx < count; ++idx)
        {
            push_back(string[idx]);
        }

        return *this;
    }

    constexpr String &operator +=(const String &string)
    {
        return append(string);
    }

    constexpr String &operator +=(CharType value)
    {
        return append(1, value);
    }

    /**
     * Unsafe if string is NOT null-terminated.
     */
    constexpr String &operator +=(const CharType *string)
    {
        size_t idx = 0;
        while (string[idx] != CharType(0))
        {
            ++idx;
        }

        return append(string, idx);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Output         ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    friend std::ostream &operator <<(std::ostream &stream, const String &string)
    {
        stream.write(string.c_str(), string.size());
        return stream;
    }
};

#endif // MY_STRING_HPP
