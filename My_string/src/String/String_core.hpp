#ifndef STRING_CORE_HPP
#define STRING_CORE_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <cassert>
#include <new>

template <typename CharType>
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
        
        if (count > sizeof(Data) / sizeof(CharType)) 
        {
            switch_to_dynamic();
            create_dynamic(string);
        }
        else 
        {
            switch_to_static();
            create_static(string);
        }
    }

    // constexpr explicit String_core(const String &other)
    // : size_(other.size_)
    // {
    //     if (other.is_dynamic())
    //     {
    //         switch_to_dynamic();
    //         create_dynamic(other.data_.data_);
    //     }
    //     else
    //     {
    //         switch_to_static();
    //         create_static(other.sso);
    //     }
    // }

    constexpr String_core(size_t count, CharType value)
    : size_(count)
    {
        if (count > sizeof(Data))
        {
            switch_to_dynamic();
            create_dynamic(value);
        }
        else
        {
            switch_to_static();
            create_static(value);
        }
    }

    constexpr String_core(const String_core &other, size_t position = 0, size_t count = other.size_)
    : size_(count)
    {
        if (other.is_dynamic())
        {
            switch_to_dynamic();
            create_dynamic(other.data_.data_ + position);
        }
        else
        {
            switch_to_static();
            create_static(other.sso + position);
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
    // --------------------- Operator =    ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core &operator=(const String_core &other)
    {
        if (other.is_dynamic()) 
        {
            if (is_dynamic()) 
            {
                if (size_ < other.size_)
                {
                    reserve_without_safety(other.capacity_);
                }

                copy_buffer(other.data_.data_, other.size_);
            }
            else
            {
                if (other.size_ > sizeof(Data))
                {
                    switch_to_dynamic(true);
                    reserve_without_safety(other.capacity_);
                }

                copy_buffer(other.data_.data_, other.size_);
            }
        } 
        else
        {
            if (is_dynamic() && size_ < other.size_)
            {
                reserve_without_safety(other.capacity_);
            }

            copy_buffer(other.data_.data_, other.size_);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Data           ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    CharType &data(index)
    {
        if (index >= size())
            throw std::out_of_range("Wrong index range\n");
            
        if (is_view_)
        {
            CharType *tmp_data = data_.data_;
            
            if (size_ > sizeof(size_t)) 
            {
                switch_to_dynamic();
                create_dynamic(tmp_data);
            }
            else 
            {
                switch_to_static();
                create_static(tmp_data, size_);
            }
        }

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

    constexpr void shrink_to_fit()
    {
        if (is_static())
        {
            return;
        }
        
        if (size_ < sizeof(Data))
        {
            switch_to_static(true);
            return;
        }

        resize(size_);
    }

    constexpr void reserve(size_t new_capacity = 0)
    {   
        if (new_capacity == 0)
        {
            shrink_to_fit();
        }

        if (new_capacity < capacity())
        {
            return;
        }

        resize(new_capacity);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operations     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void resize(size_t new_capacity, CharType value = CharType())
    {
        if (new_capacity > max_size())
        {
            return std::length_error("Too big string\n");
        }
        
        if (is_static())
        {
            if (new_capacity <= sizeof(Data))
            {
                return;
            }
            else
            {
                switch_to_dynamic(true);
            }
        }

        CharType new_buffer = new CharType[new_capacity];  // allocator
        
        size_t copy_amount = size_ < new_capacity ? size_ : new_capacity;
        for (size_t idx = 0; idx < copy_amount; ++idx)
        {
            new_buffer[idx] = data_.data_[idx];
        }

        if (copy_amount < new_capacity)
        {
            for (size_t idx = size_; idx < new_capacityl ++idx)
            {
                new_buffer[idx] = value;
            }
        }

        size_ = new_capacity;

        delete [] data_.data_;

        data_.data_     = new_buffer;
        data_.capacity_ = new_capacity;
    }

    constexpr void clear() noexcept
    {
        size_ = 0;

        switch_to_static(true);
    }

private:
    bool is_dynamic()
    {
        return is_dynamic_; // (SIZE_T_HIGH_BIT(data_.capacity_) == 1);
    }

    bool is_static()
    {
        return !is_dynamic_; // (SIZE_T_HIGH_BIT(data_.capacity_) == 0);
    }

    void switch_to_dynamic(bool switch_data = false)
    {
        is_dynamic_ = true;
        
        if (switch_data)
        {
            CharType tmp[sizeof(Data)];
            memcpy(tmp, src, sizeof(Data));

            data_.data_ = new CharType[size_ * 2];
            for (size_t idx = 0; idx < size_; ++idx)
            {
                data_.data_[idx] = tmp[idx];
            }

            data_.capacity_ = size_ * 2;
        }
    }

    void switch_to_static(bool switch_data = false)
    {
        assert(size_ < sizeof(Data));
        
        is_dynamic_ = false;

        if (switch_data)
        {
            CharType *tmp_data = data_.data_;
            for (size_t idx = 0; idx < size_; ++idx)
            {
                sso[idx] = tmp_data[idx];
            }

            delete [] data_.data_;
        }
    }

    void create_dynamic(CharType value)
    {
        size_t new_capacity = count * 2;
        CharType *new_data = new CharType[new_capacity];
        for (size_t idx = 0; idx < size_; ++idx)
        {
            new_data[idx] = value;
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
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

    void create_static(CharType value)
    {
        for (size_t idx = 0; idx < size_; ++idx)
        {
            sso[idx] = value;
        }
    }

    void create_static(const CharType *string)
    {
        for (size_t idx = 0; idx < size_; ++idx)
        {
            sso[idx] = string[idx];
        }
    }

    void reserve_without_safety(size_t new_capacity)
    {
        assert(is_dynamic());
        
        CharType *new_data = new CharType[new_capacity];

        delete [] data_.data_;
        
        data_.data_     = new_data;
        data_.capacity_ = new_capacity;
    }

    void copy_buffer(const CharType *string, size_t amount)
    {
        assert(data_.capacity_ > amount);
        
        size_ = size;
        if (is_dynamic())
        {
            for (size_t idx = 0; idx < amount; ++idx)
            {
                data_.data_[idx] = string[idx];
            }
        }
        else
        {
            for (size_t idx = 0; idx < amount; ++idx)
            {
                sso[idx] = string[idx];
            }
        }
    }
};

#endif // STRING_CORE_HPP
