#include "Static_mem.hpp"

template <typename T, size_t Size>
Static_mem<T, Size>::Static_mem() : size_(Size), resizeable(false)
{
}

template <typename T, size_t Size>
Static_mem<T, Size>::Static_mem(std::initializer_list<T> list) 
: size_(Size), resizeable(false)
{
    static_assert(list.size() <= size_, "Invalid size\n");

    for (auto idx = list.begin(), i = 0; idx != list.end(); idx++, i++)
    {
        data_[i] = idx;
    }
}

template <typename T, size_t Size>
Static_mem<T, Size>::~Static_mem()
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
    }
}

template <typename T, size_t Size>
void Static_mem<T, Size>::clear()
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
    }

    size_ = 0;
}

template <typename T, size_t Size>
void Static_mem<T, Size>::resize(size_t new_size)
{
    static_assert(resizeable, "Data can't be resized\n");
}

template <typename T, size_t Size>
void Static_mem<T, Size>::resize(size_t new_size, const T& value)
{
    static_assert(resizeable, "Data can't be resized\n");
}

// template <typename T, size_t Size>
// void Static_mem<T, Size>::push_back(const T& value)
// {
//     std::static_assert(size_ + 1 >= capacity_, "Available space limited\n");

//     data_[size_++] = value;
// }

// template <typename T, size_t Size>
// void Static_mem<T, Size>::push_back(T&& value)
// {
//     std::static_assert(size_ + 1 >= capacity_, "Available space limited\n");

//     data_[size_++] = std::move(value);
// }

// template <typename T, size_t Size>
// void Static_mem<T, Size>::pop_back()
// {
//     std::static_assert(size_ >= 0, "Nothing to pop\n");

//     data_[size_--].~T();
// }

template <typename T, size_t Size>
void Static_mem<T, Size>::swap(Static_mem<T, Size> &other)
{

}
