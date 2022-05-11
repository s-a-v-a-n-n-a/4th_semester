#ifndef STRING_CORE_HPP
#define STRING_CORE_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <cassert>
#include <new>

#include "../Sharing/Shared_ptr.hpp"

template <typename CharType>
class String_core
{
private:
    friend class Shared_ptr_cut<String_core>;
    friend class Shared_data<String_core>;

    enum class State
    {
        SSO, 
        DYNAMIC,
        VIEW,
        NON_POSSESING
    };
    
    struct Data
    {
        CharType *data_;
        size_t capacity_;
    };

    union
    {
        Data data_;
        CharType sso[0];
        Shared_ptr_cut<String_core> shared_data_;
    };

    size_t size_{0};

    State state_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors   ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core() 
    : data_{},
      size_(0), 
      state_(State::SSO)
    {}

    constexpr String_core(const CharType *string, size_t count)
    : data_{}
    {
        if (count > max_sso_size()) 
        {
            switch_to_dynamic();
            create_dynamic(string, count);
        }
        else 
        {
            switch_to_static();
            create_static(string, count);
        }
    }

    constexpr String_core(size_t count, CharType value)
    {
        if (count > max_sso_size())
        {
            switch_to_dynamic();
            create_dynamic(value, count);
        }
        else
        {
            switch_to_static();
            create_static(value, count);
        }
    }

    constexpr String_core(const String_core &other, size_t position, size_t count = 0)
    {
        if (count == 0)
        {
            count = other.size() - position;
        }
        
        if (other.is_dynamic())
        {
            switch_to_dynamic();
            create_dynamic(other.data_.data_ + position, count);
        }
        else
        {
            switch_to_static();
            create_static(other.sso + position, count);
        }
    }

    constexpr explicit String_core(const String_core &other)
    {
        printf("Constructor const &\n");
        
        if (!other.is_possessing())
        {
            shared_data_ = Shared_ptr_cut<String_core>(other.shared_data_);
            state_ = State::NON_POSSESING;
        }
        else
        {
            if (other.is_static() || other.is_convertible_to_static())
            {
                switch_to_static();
                create_static(other.sso, other.size());
            }
            else
            {
                switch_to_dynamic();
                create_dynamic(other.data_.data_, other.size());
            }
        }
    }

    constexpr explicit String_core(String_core &other)
    {
        printf("Constructor &\n");
        
        if (!other.is_possessing())
        {
            printf("not possessing\n");
            
            shared_data_ = Shared_ptr_cut(other.shared_data_);
            state_ = State::NON_POSSESING;
        }
        else
        {
            if (other.is_static())
            {
                printf("static\n");
                
                switch_to_static();
                create_static(other.sso, other.size());
            }
            else
            {
                printf("dynamic\n");
                
                other.switch_to_non_possessing();
                shared_data_ = Shared_ptr_cut(other.shared_data_);
                state_ = State::NON_POSSESING;
            }
        }
    }

    constexpr String_core(String_core &&other)
    : size_(other.size_), 
      state_(other.state_)
    {
        if (other.is_view())
        {
            data_.data_ = other.data_.data_;
            other.data_.data_ = nullptr;

            return;
        }
        
        if (other.is_possessing())
        {
            if (is_dynamic())
            {
                if (is_convertible_to_static())
                {
                    create_static(other.data_.data_, other.size());
                }
                else
                {
                    create_dynamic(other.data_.data_, other.size());
                }

                delete [] other.data_.data_;
            }
            else
            {
                create_static(other.sso, other.size());
            }
        }
        else
        {
            shared_data_ = std::move(other.shared_data_);
            other.switch_to_static();
            other.size_ = 0;
        }
    }

    static String_core view(CharType **buffer, size_t count)
    {
        String_core result{};

        result.data_.data_ = *buffer;
        result.data_.capacity_ = count;
        result.size_ = count;

        result.state_ = State::VIEW;

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Destructor     ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ~String_core()
    {
        switch(state_)
        {
        case State::DYNAMIC:
            delete data_.data_;
            break;
        case State::NON_POSSESING:
            shared_data_.~Shared_ptr_cut();
            break;
        default:
            break;
        }
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
                    reserve_without_safety(other.capacity());
                }
            }
            else
            {
                if (other.size() > max_sso_size())
                {
                    switch_to_dynamic(true);
                    reserve_without_safety(other.capacity());
                }
            }

            // copy_buffer(other.data_.data_, other.size_);
        } 
        else
        {
            if (is_dynamic() && size_ < other.size_)
            {
                reserve_without_safety(other.capacity());
            }

            // copy_buffer(other.sso, other.size_);
        }

        copy_buffer(other, other.size());

        return *this;
    }

    constexpr String_core &operator=(String_core &&other)
    {
        if (other.is_dynamic()) 
        {
            if (is_dynamic()) 
            {
                delete [] data_.data_;
            }
            else
            {
                switch_to_dynamic();
            }

            data_.data_ = std::move(other.data_.data_);
            data_.capacity_ = other.capacity_;

            data_.size_ = other.size_;
        } 
        else
        {
            if (is_dynamic()) 
            {
                delete [] data_.data_;
                switch_to_static();
            }

            memcpy(sso, other.sso, max_sso_size());
        }

        return *this;
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
            throw std::out_of_range("Wrong index range to get the element\n");

        if (!is_possessing())
        {
            switch_to_possessing();
        }

        if (is_dynamic())
            return data_.data_[index];
        else
            return sso[index];
    }

    CharType &data(size_t index) const 
    {
        if (index >= size())
            throw std::out_of_range("Wrong index range to get the element\n");

        if (is_dynamic())
            return data_.data_[index];
        else
            return sso[index];
    }

    constexpr const CharType *c_str() const
    {
        if (is_static())
        {
            printf("I am returning sso.\n");
            
            return sso;
        }
        
        if (!is_possessing())
        {
            printf("I am returning non posessed data: %p.\n", shared_data_->data_.data_);
            
            return shared_data_->data_.data_;
        }

        printf("I am returning just data.\n");
        
        return data_.data_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity       ----------------------------------------------------------------
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
            return max_sso_size();
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
        
        if (size_ < max_sso_size())
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
            if (new_capacity <= max_sso_size())
            {
                return;
            }
            else
            {
                switch_to_dynamic(true);
            }
        }

        ++new_capacity;
        CharType *new_buffer = new CharType[new_capacity];  // allocator
        
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
            throw std::length_error("Too big required size for string in resize\n");
        }
        
        if (is_static())
        {
            if (new_capacity > max_sso_size())
            {
                switch_to_dynamic(true);
            }
            else
                return;
        }

        CharType *new_buffer = new CharType[new_capacity + 1];  // allocator
        
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
    size_t max_sso_size() const noexcept
    {
        return sizeof(Data) / sizeof(CharType);
    }
    
    bool is_view() const noexcept
    {
        return state_ == State::VIEW;
    }

    bool is_possessing() const noexcept
    {
        return state_ != State::NON_POSSESING;
    }

    void switch_to_possessing()
    {
        if (shared_data_->is_dynamic())
        {
            // CharType *new_data = new CharType[size_ * 2];
            CharType *copy_on_write_data = shared_data_->data_.data_;
            
            shared_data_.~Shared_ptr_cut();
            
            // for (size_t idx = 0; idx < size_; ++idx)
            // {
            //     new_data[idx] = copy_on_write_data[idx];
            // }

            // data_.data_ = new_data;
            switch_to_dynamic();
            copy_buffer(copy_on_write_data, size_);
            
            data_.capacity_ = size_ * 2;
        }
        else
        {
            CharType tmp[max_sso_size()];
            memcpy(tmp, shared_data_->sso, max_sso_size());
            
            shared_data_.~Shared_ptr_cut();

            // for (size_t idx = 0; idx < size_; ++idx)
            // {
            //     sso[idx] = tmp[idx];
            // }
            
            switch_to_static();
            copy_buffer(tmp, size_);
        }
    }

    void switch_to_non_possessing()
    {
        Shared_data<String_core> *new_data = new Shared_data<String_core>(std::move(*this));
        Shared_ptr_cut<String_core> new_shared_ptr(new_data);
        shared_data_ = std::move(new_shared_ptr);

        state_ = State::NON_POSSESING;
    }

    void switch_to_other_possessing()
    {
        ;
    }

    bool is_dynamic() const noexcept
    {
        return state_ == State::DYNAMIC;
    }

    bool is_static() const noexcept
    {
        return state_ == State::SSO;
    }

    bool is_convertible_to_static() const noexcept
    {
        if (size_ < max_sso_size())
        {
            return true;
        }

        return false;
    }

    void switch_to_dynamic(bool switch_data = false)
    {
        state_ = State::DYNAMIC;
        
        if (switch_data)
        {
            CharType tmp[max_sso_size()];
            memcpy(tmp, sso, max_sso_size());

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
        assert(size_ < max_sso_size());
        
        state_ = State::SSO;

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

    void create_dynamic(CharType value, size_t size)
    {
        size_ = size;
        switch_to_dynamic();
        
        size_t new_capacity = size * 2;
        CharType *new_data = new CharType[new_capacity];
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            new_data[idx] = value;
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_dynamic(const CharType *string, size_t size)
    {
        size_ = size;
        switch_to_dynamic();

        size_t new_capacity = size * 2;
        CharType *new_data = new CharType[new_capacity];
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            new_data[idx] = string[idx];
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_static(CharType value, size_t size)
    {
        size_ = size;
        assert(size_ <= max_sso_size());
        
        switch_to_static();
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            sso[idx] = value;
        }
    }

    void create_static(const CharType *string, size_t size)
    {
        size_ = size;
        assert(size <= max_sso_size());
        
        switch_to_static();
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            sso[idx] = string[idx];
        }
    }

    void reserve_without_safety(size_t new_capacity)
    {
        assert(is_dynamic());
        
        CharType *new_data = new CharType[new_capacity];

        if (data_.data_)
            delete [] data_.data_;
        
        data_.data_     = new_data;
        data_.capacity_ = new_capacity;
    }

    void copy_buffer(const String_core &string, size_t amount)
    {
        copy_buffer(string.c_str(), amount);
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
