#ifndef STATIC_MEM_HPP
#define STATIC_MEM_HPP

#include <cstdio>
#include <initializer_list>

template <typename T, size_t Size>
class Static_mem
{
private:
    T data_[Size];

    const size_t size_;

    static bool resizeable;

public: 
    Static_mem();
    Static_mem(std::initializer_list<T> list);

    ~Static_mem();

    // Size
    size_t get_capacity() const { return capacity_; }

    // Data
    T &data(size_t index);

    // Capacity
    bool empty() { return (size_ == 0) }
    size_t size() const { return size_; }
    size_t capacity() const { return get_capacity(); }
    // size_t max_size();
    // void shrink_to_fit() {} 

    // Element access

    // Modifiers
    void clear();

    void resize();
    // void push_back(const T& value); 
    // void push_back(T&& value); 
    // void pop_back();
    void swap(Static_mem<T, Size> &other);
};

#endif // STATIC_MEM_HPP
