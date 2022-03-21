#ifndef DYNAMIC_MEM_HPP
#define DYNAMIC_MEM_HPP

#include <cstdio>
#include <initializer_list>

template <typename T, size_t Size = 25>
class Dynamic_mem
{
private:
    T *data_;
    
    size_t size_;
    size_t capacity_;

    static bool resizeable;

public:
    Dynamic_mem();
    Dynamic_mem(size_t amount, const T& initial_element);
    Dynamic_mem(std::initializer_list<T> list);

    ~Dynamic_mem();

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

#endif // DYNAMIC_MEM_HPP