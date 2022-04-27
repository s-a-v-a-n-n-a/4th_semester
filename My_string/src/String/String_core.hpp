#ifndef STRING_CORE_HPP
#define STRING_CORE_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <new>

class String_core
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
        CharType sso[0];
    };

    size_t size_;

    bool is_dynamic_;
    bool is_view_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core() 
    : data_{},
      size_(0), 
      is_dynamic_(true), 
      is_view_(false) 
    {}

    constexpr String_core(const CharType *string, size_t count)
    {
        size_ = count;
        
        if (count > sizeof(Data)) 
        {
            switch_to_dynamic();
            create_dynamic(string);
        }
        else 
        {
            switch_to_static();
            create_static(string, count);
        }
    }

    constexpr explicit String_core(const String &other)
    : size_(other.size_)
    {
        if (other.is_dynamic())
        {
            switch_to_dynamic();
            create_dynamic(other.data_.data_);
        }
        else
        {
            switch_to_static();
            create_static(other.sso, size_);
        }
    }

    static String_core view(CharType **buffer, size_t count)
    {
        String result{};

        result.data_.data_ = *buffer;
        result.data_.capacity_ = count;
        result.size_ = count;

        result.is_view_ = true;

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Data           ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    CharType &data(index)
    {
        if (index >= size())
            throw std::out_of_range("Wrong index range\n");
            
        // if (is_view_)
        // {
        //     CharType *tmp_data = data_.data_;
            
        //     if (size_ > sizeof(size_t)) 
        //     {
        //         switch_to_dynamic();
        //         create_dynamic(tmp_data);
        //     }
        //     else 
        //     {
        //         switch_to_static();
        //         create_static(tmp_data, size_);
        //     }
        // }

        if (is_dynamic_)
            return data_.data_[index];
        else
            return sso[index];
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity      ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    [[nodiscard]] size_t size()
    {
        return size_;
    }

    [[nodiscard]] size_t capacity()
    {
        if (is_dynamic_)
            return data_.capacity_;
        else
            return sizeof(Data);
    }

private:
    bool is_dynamic()
    {
        return is_dynamic_;// (SIZE_T_HIGH_BIT(data_.capacity_) == 1);
    }

    bool is_static()
    {
        return !is_dynamic_;// (SIZE_T_HIGH_BIT(data_.capacity_) == 0);
    }

    void switch_to_dynamic()
    {
        is_dynamic_ = true;
        // data_.size_ |= (1 << sizeof(size_t));
    }

    void switch_to_static()
    {
        is_dynamic_ = false;
        // data_.size &=  ~(1 << sizeof(size_t));
    }

    void create_dynamic(const CharType *string)
    {
        size_t new_capacity = size_ * 2;
        CharType *new_data = new CharType[new_capacity];
        for (size_t idx = 0; idx < size_; ++idx)
        {
            new_data[idx] = string[idx];
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_static(const CharType *string, size_t count)
    {
        for (size_t idx = 0; idx < size_; ++idx)
        {
            sso[idx] = string[idx];
        }
    }
};

#endif // STRING_CORE_HPP
