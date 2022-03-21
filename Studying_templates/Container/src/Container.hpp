#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstdio>
#include <initializer_list>

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
    const T &operator [] (const size_t index);
};

//////////////////////////////////////////////////////////////////////////////////////

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
class Container<bool, Size, Storage> : public Storage<unsigned char, Size>
{
private:
    struct Bool_wrapper
    {
        size_t index_;
        unsigned char bit_;

        bool value_;
    
        operator bool() const { return value_; }
    };

public:
    Container();

    // Element access
    const bool operator [] (const size_t index); 

    // Size
    size_t get_capacity() const { return capacity_; }

    // Data
    T &data(size_t index);

    // Capacity
    bool empty() { return (size_ == 0) }
    size_t size() const { return size_; }
    size_t capacity() const { return get_capacity(); }
    size_t max_size();
    void shrink_to_fit();  

    // Element access

    // Modifiers
    void clear();

    void resize();
    void push_back(const T& value); 
    void push_back(T&& value); 

    template<class... Args> 
    void emplace_back(Args&&... args);
    
    void pop_back();
    void swap(Dynamic_mem &other);
};

#endif // CONTAINER_HPP
