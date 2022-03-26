#include "Static_mem.hpp"

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

