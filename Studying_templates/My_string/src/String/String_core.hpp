#ifndef STRING_CORE_HPP
#define STRING_CORE_HPP

#include <cstdlib>
#include <cstdint>

#include <cstring>

#include <stdexcept>
#include <cassert>
#include <new>

#include <iostream>

#include "../Sharing/Shared_ptr.hpp"

#define WRONG_INDEX_RANGE \
    char info[256] = ""; \
    ssize_t element = index; \
    sprintf(info, "Wrong index range in getting acces to data: %zd\n", element); \
    throw std::out_of_range(info); \

template 
<
    typename Char_type,
    template <typename Allocator_type> class Allocator
>
class String_core
{
private:
    friend class Shared_data<String_core>;
    friend class Shared_ptr_cut<String_core, Allocator>;

    using Shared_ptr = Shared_ptr_cut<String_core, Allocator>;
    using String_allocator = Allocator<Char_type>;

    String_allocator allocator_;

    enum class State
    {
        SSO, 
        DYNAMIC,
        VIEW,
        NON_POSSESING
    };
    
    struct Data
    {
        Char_type *data_;
        size_t capacity_;
    };

    union
    {
        Data data_;
        Shared_ptr shared_data_;
        Char_type sso[0];
    };

    size_t size_{0};

    State state_;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors ------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core() 
    : allocator_(String_allocator()),
      data_{},
      size_(0), 
      state_(State::SSO)
    {}

    constexpr String_core(const Char_type *string, size_t count, const String_allocator &allocator = Allocator())
    : allocator_(allocator),
      data_{}
    {
        if (count >= max_sso_size()) 
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

    constexpr String_core(size_t count, Char_type value, const String_allocator &allocator = Allocator())
    : allocator_(allocator)
    {
        if (count >= max_sso_size())
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

    constexpr String_core(const String_core &other, size_t position, size_t count = 0, const String_allocator &allocator = Allocator())
    : allocator_(allocator)
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

    constexpr explicit String_core(const String_core &other, const String_allocator &allocator = Allocator())
    : allocator_(allocator)
    {
        if (!other.is_possessing())
        {
            share_other_possessing(other);
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

    constexpr explicit String_core(String_core &other, const String_allocator &allocator = Allocator())
    : allocator_(allocator)
    {
        if (!other.is_possessing())
        {
            share_other_possessing(other);
        }
        else
        {
            if (other.is_static())
            {
                switch_to_static();
                create_static(other.sso, other.size());
            }
            else
            {
                switch_to_other_possessing(other);
            }
        }
    }

    constexpr String_core(String_core &&other, const String_allocator &allocator = String_allocator())
    : allocator_(allocator),
      size_(other.size_), 
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

            return;
        }
        
        shared_data_ = std::move(other.shared_data_);
        other.switch_to_static();
        other.size_ = 0;
    }

    static String_core view(Char_type **buffer, size_t count)
    {
        String_core result{};

        result.data_.data_ = *buffer;
        result.data_.capacity_ = count;
        result.size_ = count;

        result.state_ = State::VIEW;

        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Destructor --------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ~String_core()
    {
        switch(state_)
        {
        case State::DYNAMIC:
            allocator_.deallocate(data_.data_, data_.capacity_);
            break;
        case State::NON_POSSESING:
            shared_data_.~Shared_ptr();
            break;
        default:
            break;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Operator = --------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr String_core &operator=(const String_core &other)
    {
        if (!other.is_possessing())
        {
            share_other_possessing(other);
        }
        else 
        {
            if (!is_possessing())
            {
                switch_to_possessing();
            }
            
            if (other.is_dynamic()) 
            {
                if (is_dynamic()) 
                {
                    if (size_ < other.size())
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
            } 
            else
            {   
                if (is_dynamic() && size_ < other.size())
                {
                    reserve_without_safety(other.capacity());
                }
            }
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
    
    Char_type &data_at(size_t index)
    {
        if (index >= size())
        {
            WRONG_INDEX_RANGE
        }

        if (!is_possessing())
        {
            switch_to_possessing();
        }

        if (is_dynamic() || is_view())
        {
            return data_.data_[index];
        }
        else
        {
            return sso[index];
        }
    }

    const Char_type &data_at(size_t index) const 
    {
        if (index >= size())
        {
            WRONG_INDEX_RANGE
        }

        if (is_dynamic() || is_view())
        {
            return data_.data_[index];
        }
        else if (is_static())
        {
            return sso[index];
        }
        else
        {
            return shared_data_->data_.data_[index];
        }
    }

    constexpr const Char_type *c_str() const
    {
        if (is_static())
        {
            return sso;
        }
        
        if (!is_possessing())
        {
            return shared_data_->data_.data_;
        }

        return data_.data_;
    }

    constexpr Char_type *data()
    {
        if (!is_possessing())
        {
            switch_to_possessing();
        }
        
        if (is_static())
        {
            return sso;
        }

        return data_.data_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity ----------------------------------------------------------------------
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
        Char_type *new_buffer = allocator_.allocate(new_capacity);
        
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
    // --------------------- Operations --------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void expand(Char_type value)
    {
        if (size() + 2 >= capacity()) // + 2 because of null-terminating
        {
            reserve(capacity() * 2);
        }

        if (is_dynamic())
        {   
            data_.data_[size()] = value;
            data_.data_[size() + 1] = Char_type(0);
        }
        else
        {
            sso[size()] = value;
            sso[size() + 1] = Char_type(0);
        }

        ++size_;
    }

    constexpr void shrink()
    {
        --size_;
        if (is_dynamic())
        {
            data_.data_[size_] = Char_type(0);
        }
        else
        {
            sso[size_] = Char_type(0);
        }

        if (size() < capacity() / 4 && !is_view())
        {
            resize(capacity() / 2);
        }
    }
    
    constexpr void resize(size_t new_capacity, Char_type value = Char_type())
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

        Char_type *new_buffer = allocator_.allocate(new_capacity + 1);
        
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

    /*constexpr void swap(String_core &other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value
                                                    || std::allocator_traits<Allocator>::is_always_equal::value)
    {
        switch(state_)
        {
        case State::SSO:
        {
            switch(other.state_)
            {
            case State::SSO:
            {
                for (size_t idx = 0; idx < max_sso_size(); ++idx)
                {
                    std::swap(sso[idx], other.sso[idx]);
                }
                break;
            }
            case State::DYNAMIC:  
            { 
                Char_type *other_data = other.data_.data_;
                size_t other_capacity = other.data_.capacity_;

                other.create_static(sso, size_);

                switch_to_dynamic();
                data_.data_ = other_data;
                data_.capacity_ = other_capacity;
                
                break; 
            }
            case State::VIEW:
            {
                Char_type *other_data = other.data_.data_;
                size_t other_capacity = other.data_.capacity_;

                other.create_static(sso, size_);

                switch_to_view();
                data_.data_ = other_data;
                data_.capacity_ = other_capacity;

                break;
            }
            case State::NON_POSSESING:
            {
                Shared_ptr other_shared_ptr = std::move(other.shared_data_);

                other.create_static(sso, size_);

                shared_data_ = std::move(other_shared_ptr);
                state_ = State::NON_POSSESING;

                break;
            }
            default:
                break;
            }
            break;
        }
        case State::DYNAMIC:
            switch(other.state_)
            {
            case State::SSO:
            {
                Char_type *current_data = data_.data_;
                size_t current_capacity = data_.capacity_;

                create_static(other.sso, other.size());
                other.create_dynamic(current_data, current_capacity);

                break;
            }
            case State::DYNAMIC:
                std::swap(data_.data_, other.data_.data_);
                std::swap(data_.capacity_, other.data_.capacity_);

                break;
            }
            case State::VIEW:
            {
                
                break;
            }
            break;
        case State::VIEW:
            break;
        case State::NON_POSSESING:
            break;
        default:
            break;
        }

        std::swap(size_, other.size_);
    } */

private:
    size_t max_sso_size() const noexcept
    {
        return sizeof(Data) / sizeof(Char_type);
    }
    
    bool is_view() const noexcept
    {
        return state_ == State::VIEW;
    }

    void switch_to_view() noexcept
    {
        state_ = State::VIEW;
    }

    bool is_possessing() const noexcept
    {
        return state_ != State::NON_POSSESING;
    }

    void switch_to_possessing()
    {
        if (shared_data_->is_dynamic())
        {
            Char_type *copy_on_write_data = shared_data_->data_.data_;
            
            shared_data_.~Shared_ptr();
            
            switch_to_dynamic();
            
            data_.data_ = allocator_.allocate(size_ * 2);
            copy_buffer(copy_on_write_data, size_);
            
            data_.capacity_ = size_ * 2;
        }
        else
        {
            Char_type tmp[max_sso_size()];
            memcpy(tmp, shared_data_->sso, max_sso_size());
            
            shared_data_.~Shared_ptr();

            switch_to_static();
            copy_buffer(tmp, size_);
        }
    }

    void switch_to_non_possessing()
    {
        Shared_ptr new_shared_ptr(this);
        shared_data_ = std::move(new_shared_ptr);

        state_ = State::NON_POSSESING;
    }

    void switch_to_other_possessing(String_core &other)
    {
        other.switch_to_non_possessing();
        shared_data_ = Shared_ptr(other.shared_data_);
        size_ = other.size_;
        state_ = State::NON_POSSESING;
    }

    void share_other_possessing(const String_core &other)
    {
        shared_data_ = Shared_ptr(other.shared_data_);
        size_ = other.size_;
        state_ = State::NON_POSSESING;
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
            Char_type tmp[max_sso_size()];
            memcpy(tmp, sso, max_sso_size());

            Char_type *new_data = allocator_.allocate(size_ * 2);
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
            Char_type *tmp_data = data_.data_;
            for (size_t idx = 0; idx < size_; ++idx)
            {
                sso[idx] = tmp_data[idx];
            }

            delete [] data_.data_;
        }
    }

    void create_dynamic(Char_type value, size_t size)
    {
        // std::cout << "Creating dynamic from value\n";
        
        size_ = size;
        switch_to_dynamic();
        
        size_t new_capacity = size * 2;
        Char_type *new_data = allocator_.allocate(new_capacity);
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            new_data[idx] = value;
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_dynamic(const Char_type *string, size_t size)
    {
        // std::cout << "Creating dynamic from string\n";
        
        size_ = size;
        switch_to_dynamic();

        size_t new_capacity = size * 2;
        Char_type *new_data = allocator_.allocate(new_capacity);
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            new_data[idx] = string[idx];
        }

        data_.data_ = new_data;
        data_.capacity_ = new_capacity;
    }

    void create_static(Char_type value, size_t size)
    {
        // std::cout << "Creating static from value\n";
        
        size_ = size;
        assert(size_ <= max_sso_size());
        
        switch_to_static();
        
        for (size_t idx = 0; idx < size; ++idx)
        {
            sso[idx] = value;
        }
    }

    void create_static(const Char_type *string, size_t size)
    {
        // std::cout << "Creating static from string\n";
        
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
        
        ++new_capacity;
        Char_type *new_data = allocator_.allocate(new_capacity);

        if (data_.data_)
        {
            delete [] data_.data_;
        }
        
        data_.data_     = new_data;
        data_.capacity_ = new_capacity;
    }

    void copy_buffer(const String_core &string, size_t amount)
    {
        copy_buffer(string.c_str(), amount);
    }

    void copy_buffer(const Char_type *string, size_t amount)
    {        
        if (is_dynamic())
        {
            assert(capacity() > amount);
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
        size_ = amount;
    }
};

#endif // STRING_CORE_HPP
