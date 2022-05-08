#ifndef STRING_CORE_HPP
#define STRING_CORE_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <cassert>
#include <new>

#include "../Sharing/Shared_ptr.hpp"

enum class New_param
{
    ZEROING = 0
};

void *operator new[](size_t size, New_param parameter)
{
    if (void *ptr = calloc(size, sizeof(unsigned char)))
    {
        return ptr;
    }
        
    throw std::bad_alloc{};
}

template <typename CharType>
class String_core
{
private:
    friend class Shared_ptr_cut<String_core>;
    friend class Shared_data<String_core>;

    struct Data
    {
        CharType *data_;
        size_t capacity_;
    };

    union
    {
        Data data_;
        CharType sso[0];
        Shared_ptr_cut<Shared_data<String_core>> shared_data;
    };

    size_t size_;

    bool is_dynamic_;
    bool is_view_;
    bool is_possessing_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core() 
    : data_{},
      size_(0), 
      is_dynamic_(true), 
      is_view_(false),
      is_possessing_(true) 
    {}

    constexpr String_core(const CharType *string, size_t count)
    : data_{},
      size_(count), 
      is_view_(false),
      is_possessing_(true) 
    {
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
    : size_(count),
      is_view_(false),
      is_possessing_(true)
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

    constexpr String_core(const String_core &other, size_t position = 0, size_t count = 0)
    : is_view_(false),
      is_possessing_(true)
    {
        if (count == 0)
        {
            count = other.size() - position;
        }
        size_ = count;
        
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

    constexpr String_core(String_core &&other)
    : size_(other.size_), 
      is_dynamic_(other.is_dynamic_), 
      is_view_(other.is_view_),
      is_possessing_(other.is_possessing_) 
    {
        if (is_possessing())
        {
            other.switch_to_non_possessing();
        }
        else
        {

        }
    }

    static String_core view(CharType **buffer, size_t count)
    {
        String_core result{};

        result.data_.data_ = *buffer;
        result.data_.capacity_ = count;
        result.size_ = count;

        result.is_view_ = true;
        result.is_possessing_ = true;

        return result;
    }

    static String_core copy_on_write(String_core &other)
    {
        String_core result{};

        result.copy_on_write = const_cast(Shared_ptr_cut<String_core<CharType>&>(&other));
        result.size_ = other.size_;

        result.is_view_ = false;
        result.is_possessing_ = false;

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Destructor     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ~String_core()
    {
        ;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operator =     ----------------------------------------------------------------
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
    // --------------------- Element access ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    CharType *no_null_data() const
    {
        if (is_dynamic())
        {
            return data_.data_;
        }
        else
        {
            return sso;
        }
    }
    
    CharType &data(size_t index)
    {
        if (index >= size())
            throw std::out_of_range("Wrong index range\n");

        if (!is_possessing())
        {
            switch_to_possessing();
        }
            
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
                create_static(tmp_data);
            }
        }

        if (is_dynamic_)
            return data_.data_[index];
        else
            return sso[index];
    }

    constexpr const CharType *c_str() const
    {
        if (is_static())
        {
            if (size_ < sizeof(Data))
            {
                return sso;
            }
            // switch_to_dynamic(true);
        }

        return data_.data_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity      ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    [[nodiscard]] size_t size() const
    {
        return size_;
    }

    [[nodiscard]] size_t capacity() const
    {
        if (is_dynamic())
            return data_.capacity_;
        else
            return sizeof(Data);
    }

    [[nodiscard]] size_t max_size() const
    {
        return SIZE_MAX - 1;
    }

    constexpr void shrink_to_fit()
    {
        assert(!is_view());
        
        if (!is_possessing())
        {
            switch_to_possessing();
        }
        
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
        assert(!is_view());

        if (!is_possessing())
        {
            switch_to_possessing();
        }
        
        if (new_capacity == 0)
        {
            shrink_to_fit();
        }

        if (new_capacity < capacity())
        {
            return;
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

        ++new_capacity;
        CharType *new_buffer = new (New_param::ZEROING) CharType[new_capacity];  // allocator
        
        size_t copy_amount = size_;
        for (size_t idx = 0; idx < copy_amount; ++idx)
        {
            new_buffer[idx] = data_.data_[idx];
        }

        memset((char*)data_.data_, 0, new_capacity - copy_amount);

        delete [] data_.data_;

        data_.data_     = new_buffer;
        data_.capacity_ = new_capacity;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operations     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void expand(CharType value)
    {
        if (size() + 2 >= capacity()) // + 2 because of null-terminating
        {
            reserve(capacity() * 2);
        }

        if (is_dynamic())
        {   
            data_.data_[size()] = value;
            data_.data_[size() + 1] = CharType(0);
        }
        else
        {
            sso[size()] = value;
            sso[size() + 1] = CharType(0);
        }

        ++size_;
    }

    constexpr void shrink()
    {
        --size_;
        if (is_dynamic())
        {
            data_.data_[size_] = CharType(0);
        }
        else
        {
            sso[size_] = CharType(0);
        }

        if (size() < capacity() / 4 && !is_view())
        {
            resize(capacity() / 2);
        }
    }
    
    constexpr void resize(size_t new_capacity, CharType value = CharType())
    {
        assert(!is_view()); 

        if (!is_possessing())
        {
            switch_to_possessing();
        }
       
        if (new_capacity > max_size())
        {
            throw std::length_error("Too big string\n");
        }
        
        if (is_static())
        {
            if (new_capacity > sizeof(Data))
            {
                switch_to_dynamic(true);
            }
            else
                return;
        }

        CharType *new_buffer = new (New_param::ZEROING) CharType[new_capacity + 1];  // allocator
        
        size_t copy_amount = size_ < new_capacity ? size_ : new_capacity;
        for (size_t idx = 0; idx < copy_amount; ++idx)
        {
            new_buffer[idx] = data_.data_[idx];
        }

        if (copy_amount < new_capacity)
        {
            for (size_t idx = size_; idx < new_capacity; ++idx)
            {
                new_buffer[idx] = value;
            }
        }

        size_ = new_capacity;

        delete [] data_.data_;

        data_.data_     = new_buffer;
        data_.capacity_ = new_capacity + 1;
    }

    constexpr void clear() noexcept
    {
        size_ = 0;

        switch_to_static(true);
    }

private:
    bool is_view() const
    {
        return is_view_;
    }

    bool is_possessing() const
    {
        return is_possessing_;
    }

    void switch_to_possessing()
    {
        if (copy_on_write.is_dynamic())
        {
            CharType *new_data = new CharType[size_ * 2];
            CharType *copy_on_write_data = copy_on_write.data_.data_;
            
            copy_on_write.~Shared_ptr_cut();
            
            for (size_t idx = 0; idx < size_; ++idx)
            {
                new_data[idx] = copy_on_write_data[idx];
            }

            data_.data_ = new_data;
            data_.capacity_ = size_ * 2;

            switch_to_dynamic();
        }
        else
        {
            CharType tmp[sizeof(Data)];
            memcpy(tmp, copy_on_write.sso, sizeof(Data) / sizeof(CharType));
            
            copy_on_write.~Shared_ptr_cut();

            for (size_t idx = 0; idx < size_; ++idx)
            {
                sso[idx] = tmp[idx];
            }

            switch_to_static();
        }

        is_possessing_ = true;
    }

    bool is_dynamic() const
    {
        return is_dynamic_;
    }

    bool is_static() const
    {
        return !is_dynamic_;
    }

    void switch_to_dynamic(bool switch_data = false)
    {
        is_dynamic_ = true;
        
        if (switch_data)
        {
            CharType tmp[sizeof(Data)];
            memcpy(tmp, sso, sizeof(Data) / sizeof(CharType));

            CharType *new_data = new CharType[size_ * 2];
            for (size_t idx = 0; idx < size_; ++idx)
            {
                new_data[idx] = tmp[idx];
            }

            data_.data_ = new_data;
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
        // printf("create dynamic with value\n");
        
        size_t new_capacity = size_ * 2;
        CharType *new_data = new (New_param::ZEROING) CharType[new_capacity];
        for (size_t idx = 0; idx < size_; ++idx)
        {
            new_data[idx] = value;
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_dynamic(const CharType *string)
    {
        // printf("create dynamic with string\n");
        
        size_t new_capacity = size_ * 2;
        CharType *new_data = new (New_param::ZEROING) CharType[new_capacity];
        for (size_t idx = 0; idx < size_; ++idx)
        {
            // printf("Copying\n");
            new_data[idx] = std::move(string[idx]);
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
        
        size_ = amount;
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
