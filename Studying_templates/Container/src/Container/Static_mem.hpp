#ifndef STATIC_MEM_HPP
#define STATIC_MEM_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <utility>
#include <initializer_list>

template <typename T, size_t Size>
class Static_memory
{
protected:
    T data_[Size];

    const size_t size_;

    const bool resizeablef_{false};

public: 
    Static_memory() : size_(Size) {}
    Static_memory(std::initializer_list<T> list)
    : size_(Size)
    {
        // static_assert(list.size() <= size_, "Invalid size\n");

        for (auto idx = list.begin(), i = 0; idx != list.end(); idx++, i++)
        {
            data_[i] = idx;
        }
    }

    ~Static_memory()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i].~T();
        }
    }

    // ------------ Size ------------------------------------
    size_t get_capacity() const { return size_; }

    // ------------ Data ------------------------------------
    T &data(size_t index);

    // ------------ Capacity --------------------------------
    bool empty() const { return (size_ == 0); }
    size_t size() const { return size_; }
    size_t capacity() const { return size(); }
    size_t max_size() const { return size(); }
    void shrink_to_fit() 
    {
        assert(resizeable_); // , "Data can't be resized\n"
    } 

    // ------------ Modifiers --------------------------------
    void clear()
    {
        assert(resizeable_);
    }

    void resize(size_t new_size)
    {
        assert(resizeable_); // , "Data can't be resized\n"
    }

    void resize(size_t new_size, const T& value)
    {
        assert(resizeable_); // , "Data can't be resized\n"
    }
    
    void swap(Static_mem<T, Size> &other)
    {
        for (size_t idx = 0; idx < size_; ++idx)
        {
            T tmp = std::move(data_[idx]);

            data_[idx] = std::move(other.data_[idx]);
            other.data_[idx] = std::move(tmp);
        }
    }
};

template <size_t Size>
struct Static_mem
{
    template<typename T>
    using type = Static_memory<T, Size>;
};

#endif // STATIC_MEM_HPP
