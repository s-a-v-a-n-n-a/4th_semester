#include "Dynamic_mem.hpp"

template <typename T, size_t Size>
static bool Dynamic_mem<T, Size>::resizeable = true;

template <typename T, size_t Size>
Dynamic_mem<T, Size>::Dynamic_mem() : size_(0), capacity_(Size)
{
    data_ = (T*)calloc(Size, sizeof(T));
}

template <typename T, size_t Size>
Dynamic_mem<T, Size>::Dynamic_mem(size_t amount, const T& initial_element) : size_(0)
{
    capacity_ = (amount > Size_ ? amount : Size);
    data_ = (T*)calloc(capacity_, sizeof(T));

    for (size_t i = 0; i < amount; i++)
    {
        data_ = new T(initial_element);
    }
}

template <typename T, size_t Size>
Dynamic_mem<T, Size>::Dynamic_mem(std::initializer_list<T> list) : size_(list.size()), capacity_(Size)
{
    std::static_assert(size_ <= capacity_, "Invalid size\n");
    
    data_ = (T*)calloc(Size, sizeof(T));

    for (auto i = list.begin, j = 0; i != list.end; i++, j++)
    {
        data_[j] = new T(i);
    }
}

template <typename T, size_t Size>
Dynamic_mem<T, Size>::~Dynamic_mem()
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
    }

    free(data_);
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::shrink_to_fit()
{
    size_t new_capacity = size_;
    
    T* new_data = (T*)calloc(new_capacity, sizeof(T));
    for (size_t idx = 0; idx < size_; ++i) 
    {
        new_data[idx] = new T(std::move(data_[idx]));
    }

    data_ = new_data;
    capacity_ = new_capacity;

    free(new_data);
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::clear()
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
    }

    size_ = 0;
} 

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::resize() 
{
    std::static_assert(resizeable, "Data can't be resized\n");
    
    size_t new_capacity = capacity_ * 2;
    
    T* new_data = (T*)calloc(new_capacity, sizeof(T));
    for (size_t idx = 0; idx < size_; ++i) 
    {
        new_data[idx] = new T(std::move(data_[idx]));
    }

    data_ = new_data;
    capacity_ = new_capacity;

    free(new_data);
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::push_back(const T& value)
{
    if (size_ + 1 >= capacity_)
    {
        resize();
    }
    
    data_[size_++] = new T(value);
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::push_back(T&& value)
{
    if (size_ + 1 >= capacity_)
    {
        resize();
    }
    
    data_[size_++] = new T(value);
}

template <typename T, size_t Size>
template<class... Args> 
void Dynamic_mem<T, Size>::emplace_back(Args&&... args)
{
    if (size_ + 1 >= capacity_)
    {
        resize();
    }

    data_[size_++] = new T(std::forward<Args>(args)...);
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::pop_back()
{
    std::static_assert(size_ >= 0, "Nothing to pop\n");
    
    data_[size_--].~T();
}

template <typename T, size_t Size>
void Dynamic_mem<T, Size>::swap(Dynamic_mem &other)
{
    T* tmp_data = std::move(data_);
    data_ = std::move(other.data_);
    other.data_ = std::move(tmp_data);

    size_t tmp_capacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmp_capacity;

    size_t tmp_size = size_;
    size_ = other.size_;
    other.size_ = tmp_size; 
}
