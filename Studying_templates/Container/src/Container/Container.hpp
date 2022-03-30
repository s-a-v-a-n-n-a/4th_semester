#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstdio>
#include <initializer_list>
#include <cmath>

#include "Dynamic_mem.hpp"
#include "Static_mem.hpp"

template
<
    typename T,
    template <typename Storage_type> class Storage
>
class Container : public Storage<T>
{
private:
    typedef Storage<T> Base;

public:
    Container() : Base()
    {
    }

    Container(std::initializer_list<T> list) : Base(list) 
    {
    }

    // Element access
    T& front()
    {
        assert(Base::size_ > 0); // , "Invalid index\n"

        return Base::data_[0];
    }
    T& back()
    {
        assert(Base::size_ > 0); // , "Invalid index\n"
        
        return Base::data_[Storage<bool>::size_ - 1];
    }
    T &operator [] (const size_t index)
    { 
        assert(index < Base::size_); // , "Invalid index\n"
        
        return Base::data_[index]; 
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    // size_t Size,
    template <typename Storage_type> class Storage
>
class Container<bool, Storage> : public Storage<unsigned char> // , Size/sizeof(unsigned char) + (size_t)(Size % sizeof(unsigned char) != 0)
{
private:
    using Bool_base = Storage<unsigned char>; // , Size/sizeof(unsigned char) + (size_t)(Size % sizeof(unsigned char) != 0)

    size_t bools_amount_;

    struct Bool_wrapper
    {
        Container<bool, Storage> *source_;
        
        size_t index_;
        unsigned char bit_;

        bool value_;
    
        Bool_wrapper() = delete;
        
        Bool_wrapper(Container<bool, Storage> *source) : source_(source)
        {
            update(0);
        }
        
        explicit Bool_wrapper(size_t virtual_index)
        {
            update(virtual_index);
        }
        
        operator bool() const { return value_; }

        void update(size_t virtual_index)
        {
            index_ = virtual_index / sizeof(unsigned char);
            bit_ = virtual_index % sizeof(unsigned char);
            value_ = (source_->get_value(index_) << bit_) & 1;
        }

        void operator = (const bool other)
        {
            value_ = other;

            source_->set_value(index_, (unsigned char)(source_->get_value(index_) & ~(1 << bit_)));
            source_->set_value(index_, (unsigned char)(source_->get_value(index_) | (value_ << bit_)));
        }
    };

    Bool_wrapper wrapper;

public:
    Container() : Bool_base(), bools_amount_(0), wrapper(this) {}
    Container(size_t amount, const bool value) 
    : Bool_base(2 * amount / sizeof(unsigned char) + 
               (size_t)(2 * amount % sizeof(unsigned char) != 0), value), 
      wrapper(this)
    {
        size_t new_size = 2 * amount;
        bools_amount_ = new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0);
    }

    Container(std::initializer_list<bool> list)
    : Bool_base()
    {
        size_t list_size = list.size()/sizeof(unsigned char) + (size_t)(list.size() % sizeof(unsigned char) != 0);
        assert(list_size <= Bool_base::size_);

        size_t i = 0;
        for (auto idx = list.begin(); idx != list.end(); idx++, i++)
        {
            Bool_base::data_[i] = idx;
        }
    }

    // ------------ Elements access --------------------------------
    
    void set_value(const size_t index, const unsigned char value)
    {
        Bool_base::data_[index] = value;
    }

    unsigned char get_value(const size_t index)
    {
        return Bool_base::data_[index];
    }

    bool &front()
    {
        wrapper.update(0);
        return wrapper;
    }
    
    bool &back()
    {
        wrapper.update(bools_amount_ - 1);
        return wrapper;
    }

    Bool_wrapper &operator [] (const size_t index)
    {
        wrapper.update(index);
        return wrapper;
    }

    // ------------ Capacity --------------------------------

    size_t size() const { return bools_amount_; }
    size_t capacity() const { return capacity() * sizeof(unsigned char); }
    // size_t max_size();
    // void shrink_to_fit(); 

    // ------------ Modifiers --------------------------------

    void resize(size_t new_size)
    {
        size_t new_size_compressed = new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0);
        Bool_base::resize(new_size_compressed);
    }

    void resize(size_t new_size, const bool& value)
    {        
        unsigned char propagated_value = 0;
        if (value)
            propagated_value = (unsigned char)(-1);

        size_t new_size_compressed = std::ceil(new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0));

        Bool_base::resize(new_size_compressed, propagated_value);
    }

    void push_back(const bool& value)
    {
        if (bools_amount_ % sizeof(unsigned char) < sizeof(unsigned char) - 1)
        {
            Bool_base::push_back(0);
        }

        wrapper.update(bools_amount_++); 
        wrapper = value;
    }

    void push_back(bool&& value)
    {
        assert(Bool_base::resizeable_); // , "Data can't be resized\n"
        
        if (bools_amount_ % sizeof(unsigned char) == sizeof(unsigned char) - 1)
        {
            Bool_base::push_back((unsigned char)0);
        }

        wrapper.update(bools_amount_++); 
        wrapper = value;
    }

    void emplace_back(bool arg)
    {
        assert(Bool_base::resizeable); // , "Data can't be resized\n"
        
        push_back(arg);
    }
    
    void pop_back()
    {    
        assert(Bool_base::size_ > 0); // , "Nothing to pop\n"
        
        if (bools_amount_ % sizeof(unsigned char) == 0)
        {
            Bool_base::pop_back();
        }

        bools_amount_--;
    }
};

// TODO: how to make specialization for bools for static memory

#endif // CONTAINER_HPP