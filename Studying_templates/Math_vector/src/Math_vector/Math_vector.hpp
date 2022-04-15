#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdint>

#include <stdexcept>
#include <new>

#include <utility>
#include <initializer_list>
#include <iterator>

template <typename T, size_t Size>
class Math_vector
{
private:
    T *data_;
    size_t size_;
    size_t capacity_;

public:
    Math_vector() : data_(nullptr), size_(0), capacity_(0) {}
    Math_vector(size_t amount, const T& initial_element)
    {
        data_ = (T*)(new unsigned char[capacity_ * sizeof(T)]);

        for (size_t i = 0; i < amount; i++)
        {
            new(data_ + i) T(initial_element);
        }
    }
    explicit Math_vector(std::initializer_list<T> list)
    {
        data_ = (T*)(new unsigned char[capacity_ * sizeof(T)]);

        size_t j = 0;
        for (auto i = list.begin(); i != list.end(); i++, j++)
        {
            new(data_ + j) T(*i);
        }
    }

    [[nodiscard]] size_t size() { return size_; }

    T& operator[](int index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Array index out of range"); 
        }

        return data_[index];
    }

    T dot(Math_vector &other)
    {
        return dot<Size>(*this, other);
    }
    
private:
    template <size_t Vector_size>
    T dot(Math_vector &one, Math_vector &other)
    {
        if constexpr (Vector_size == 0)
            return 0;
        else
            return data_[Vector_size - 1] * other.data_[Vector_size - 1] + dot<Vector_size - 1>(one, other);
    }
};

#endif // MATH_VECTOR_HPP
