#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

// SIZE_MAX
#define SIZE_T_HIGH_BIT(number) (number >> sizeof(size_t))  

template <typename CharType>
class String
{
private:
    struct Data
    {
        CharType *data_;
        size_t capacity_;
    };

    union
    {
        Data data_;
        uint8_t sso[0];
    };

    size_t size_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr String(const CharType *string, size_t count)
    {
        if (count > sizeof(size_t)) 
        {
            switch_to_dynamic();
        }
        else 
        {
            switch_to_static();
        }

        data_ = new CharType[count];
        
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Element access ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr CharType &at(size_t position)
    {

    }

    CharType &operator[](size_t index)
    {

    }

    constexpr CharType &front()
    {
        
    }
    
    constexpr CharType &back()
    {
        
    }

private:
    bool is_dynamic()
    {
        return (SIZE_T_HIGH_BIT(data_.capacity_) == 1);
    }

    bool is_static()
    {
        return (SIZE_T_HIGH_BIT(data_.capacity_) == 0);
    }

    void switch_to_dynamic()
    {
        data_.size_ |= (1 << sizeof(size_t));
    }

    void switch_to_static()
    {
        data_.size &=  ~(1 << sizeof(size_t));
    }
};

#endif // MY_STRING_HPP
