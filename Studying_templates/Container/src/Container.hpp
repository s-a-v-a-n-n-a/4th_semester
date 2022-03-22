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
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
class Container : public Storage<T, Size>
{
private:

public:
    Container();
    Container(std::initializer_list<T> list);

    // Element access
    T& front();
    T& back();
    T &operator [] (const size_t index);
};

//////////////////////////////////////////////////////////////////////////////////////

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
class Container<bool, Size, Storage> : public Storage<unsigned char, ceil((float)Size/(float)sizeof(unsigned char))>
{
private:
    size_t bools_amount_;

    struct Bool_wrapper
    {
        size_t index_;
        unsigned char bit_;

        bool value_;
    
        Bool_wrapper()
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
            value_ = (data_[index_] << bit_) & 1;
        }

        void operator = (const bool& other)
        {
            value_ = other;

            data_[index_] &= ~(1 << bit_);
            data_[index_] |= (value_ << bit_);
        }
    };

    Bool_wrapper wrapper;

public:
    Container();

    // Element access
    bool& front();
    bool& back();
    bool &operator [] (const size_t index);

    // Capacity
    // bool empty() { return (size_ == 0) }
    size_t size() const { return bools_amount_; }
    size_t capacity() const { return get_capacity() * sizeof(unsigned char); }
    // size_t max_size();
    // void shrink_to_fit(); 

    // Modifiers
    // void clear();

    void resize(size_t new_size);
    void resize(size_t new_size, const bool& value);

    void push_back(const bool& value); 
    void push_back(bool&& value); 

    void emplace_back(bool arg);
    
    void pop_back();
};

#endif // CONTAINER_HPP
