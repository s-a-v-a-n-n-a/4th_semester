#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <new>

#include <iterator>

#include "String_core.hpp"

#define SIZE_T_HIGH_BIT(number) (number >> sizeof(size_t))  

template 
<
    typename Char_type,
    template <typename Allocator_type> class Allocator
> // strategy
class String : protected String_core<Char_type, Allocator>
{
private:
    typedef String_core<Char_type, Allocator> String_core;

    using String_allocator = Allocator<Char_type>;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors ------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr explicit String(const String_core &core, const String_allocator &allocator = String_allocator())
    : String_core(core, allocator)
    {}

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors ------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String() 
    : String_core()
    {}

    constexpr String(const Char_type *string, size_t count, const String_allocator &allocator = String_allocator())
    : String_core(string, count, allocator)
    {}

    /**
     * Unsafe if 
     * a) string is NOT null-terminated;
     * b) sizeof(Char_type) != 1;
     * It will be NOT safe if null can be reached in other way than last symbol
     */
    constexpr String(const Char_type *string, const String_allocator &allocator = String_allocator())
    : String_core(string, strlen(string), allocator)
    {}

    constexpr String(String &other, const String_allocator &allocator = String_allocator())
    : String_core(other, allocator)
    {}

    constexpr String(const String &other, const String_allocator &allocator = String_allocator())
    : String_core(other, allocator)
    {}

    constexpr String(const String &other, size_t position, const String_allocator &allocator = String_allocator())
    : String_core(other, position, allocator)
    {}

    constexpr String(const String &other, size_t position, size_t count, const String_allocator &allocator = String_allocator())
    : String_core(other, position, count, allocator)
    {}

    constexpr String(const String &&other, const String_allocator &allocator = String_allocator())
    : String_core(other, allocator)
    {}

    constexpr String(size_t count, Char_type value, const String_allocator &allocator = String_allocator())
    : String_core(count, value, allocator)
    {}

    static String view(Char_type **buffer, size_t count)
    {
        return String<Char_type, Allocator>(String_core::view(buffer, count));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operator = --------------------------------------------------------------------
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
    // --------------------- Capacity ----------------------------------------------------------------------
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
    
    constexpr Char_type &at(size_t position)
    {
        return (*this)[position];
    }

    Char_type &operator[](size_t index)
    {
        return String_core::data_at(index);
    }

    const Char_type &operator[](size_t index) const
    {
        return const_cast<Char_type&>((this)[index]);
    }

    constexpr Char_type &front()
    {
        return (*this)[0];
    }
    
    constexpr Char_type &back()
    {
        return (*this)[size() - 1];
    }

    using String_core::c_str;
    using String_core::data;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operations --------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using String_core::resize;

    constexpr void push_back(Char_type value)
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

    constexpr String &append(size_t count, Char_type value)
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
        
        return append(string.c_str(), count, position);
    }

    constexpr String& append(const Char_type* string, size_t count, size_t position = 0)
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

    constexpr String &operator +=(Char_type value)
    {
        return append(1, value);
    }

    /**
     * Unsafe if string is NOT null-terminated.
     */
    constexpr String &operator +=(const Char_type *string)
    {
        size_t idx = 0;
        while (string[idx] != Char_type(0))
        {
            ++idx;
        }

        return append(string, idx);
    }

    constexpr String operator+(const String &adding)
    {
        String result = *this;

        result += adding;
        return result;
    }

    // constexpr String operator+(const Char_type *adding)
    // {
    //     String result = *this;   
    // }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Comparisons -------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool operator==(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return false;
        }

        for (size_t idx = 0; idx < current_size; ++idx)
        {
            if (String_core::data_at(idx) != other.data_at(idx))
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return true;
        }

        for (size_t idx = 0; idx < current_size; ++idx)
        {
            if (String_core::data_at(idx) == other.data_at(idx))
            {
                return false;
            }
        }

        return true;
    }

    bool operator<(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return (current_size < other_size);
        }

        for (size_t idx = 0; idx < current_size - 1; ++idx)
        {
            if (String_core::data_at(idx) > other.data_at(idx))
            {
                return false;
            }
        }

        if (String_core::data_at(current_size - 1) == other.data_at(current_size - 1))
        {
            return false;
        }

        return true;
    }

    bool operator<=(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return (current_size < other_size);
        }

        for (size_t idx = 0; idx < current_size - 1; ++idx)
        {
            if (String_core::data_at(idx) > other.data_at(idx))
            {
                return false;
            }
        }

        return true;
    }

    bool operator>(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return (current_size > other_size);
        }

        for (size_t idx = 0; idx < current_size - 1; ++idx)
        {
            if (String_core::data_at(idx) < other.data_at(idx))
            {
                return false;
            }
        }

        if (String_core::data_at(current_size - 1) == other.data_at(current_size - 1))
        {
            return false;
        }

        return true;
    }

    bool operator>=(const String<Char_type, Allocator> &other) const
    {
        size_t current_size = size();
        size_t other_size = other.size();
        
        if (current_size != other_size)
        {
            return (current_size > other_size);
        }

        for (size_t idx = 0; idx < current_size - 1; ++idx)
        {
            if (String_core::data_at(idx) < other.data_at(idx))
            {
                return false;
            }
        }

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Input/Output ------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    friend std::ostream &operator <<(std::ostream &stream, const String &string)
    {
        stream.write(string.c_str(), string.size());
        return stream;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For iterator ------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Char_type *begin()
    {
        return data();
    }

    Char_type *end()
    {
        return data() + size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const iterator ------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Char_type *cbegin()
    {
        return const_iterator(begin());
    }

    Char_type *cend()
    {
        return const_iterator(end());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For reversed iterator ---------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Char_type *rbegin()
    {
        return reverse_iterator(end());
    }

    Char_type *rend()
    {
        return reverse_iterator(begin());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const reversed iterator ---------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Char_type *crbegin()
    {
        return const_reverse_iterator(end());
    }

    Char_type *crend()
    {
        return const_reverse_iterator(begin());
    }
};

#endif // MY_STRING_HPP
