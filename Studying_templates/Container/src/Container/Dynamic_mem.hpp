#ifndef DYNAMIC_MEM_HPP
#define DYNAMIC_MEM_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <utility>
#include <initializer_list>

#include <new>

template <typename T, size_t Size = 25>
class Dynamic_mem
{
protected:
    T *data_;
    
    size_t size_;
    size_t capacity_;

    const bool resizeable_{true};

public:
    Dynamic_mem() : size_(0), capacity_(Size)
    {
        // data_ = (T*)calloc(Size, sizeof(T));
        data_ = (T*)(new unsigned char[Size * sizeof(T)]);
    }

    Dynamic_mem(size_t amount, const T& initial_element) : size_(0)
    {
        capacity_ = (amount > Size ? amount : Size);
        // data_ = (T*)calloc(capacity_, sizeof(T));
        data_ = (T*)(new unsigned char[Size * sizeof(T)]);

        for (size_t i = 0; i < amount; i++)
        {
            new(data_ + i * sizeof(T)) T(initial_element);
        }
    }

    Dynamic_mem(std::initializer_list<T> list) : size_(list.size()), capacity_(Size)
    {
        static_assert(size_ <= capacity_, "Invalid size\n");
        
        // data_ = (T*)calloc(Size, sizeof(T));
        data_ = static_cast<T*>(new unsigned char[Size * sizeof(T)]);

        for (auto i = list.begin, j = 0; i != list.end; i++, j++)
        {
            new(data_ + j * sizeof(T)) T(i);
        }
    }

    ~Dynamic_mem()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i].~T();
        }

        delete [] data_;
    }

    // ------------ Size ------------------------------------
    size_t get_capacity() const { return capacity_; }

    // ------------ Data ------------------------------------
    T &data(size_t index);

    // ------------ Capacity ------------------------------------
    bool empty() { return (size_ == 0); }
    size_t size() const { return size_; }
    size_t capacity() const { return get_capacity(); }
    size_t max_size();
    void shrink_to_fit()
    {
        size_t new_capacity = size_;
        
        T* new_data = (T*)(new unsigned char[new_capacity * sizeof(T)]);
        for (size_t idx = 0; idx < size_; ++idx) 
        {
            new(new_data + idx) T(std::move(data_[idx]));
        }

        delete [] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }

    // ------------ Modifiers ------------------------------------
    void clear()
    {
        for (size_t idx = 0; idx < size_; ++idx)
        {
            data_[idx].~T();
        }

        size_ = 0;
    } 

    void resize(size_t new_size)
    {
        T* new_data = (T*)(new unsigned char[new_size * sizeof(T)]);
        for (size_t idx = 0; idx < size_; ++idx) 
        {
            new(new_data + idx) T(std::move(data_[idx]));
        }

        delete [] data_;

        data_ = new_data;
        capacity_ = new_size;
    }

    void resize(size_t new_size, const T& value)
    {
        T* new_data = (T*)(new unsigned char[new_size * sizeof(T)]);
        for (size_t idx = 0; idx < size_; ++idx) 
        {
            new(new_data + idx) T(std::move(data_[idx]));
        }
        for (size_t idx = size_; idx < new_size; ++idx)
        {
            new(new_data + idx) T(value);
        }

        delete [] data_;

        data_ = new_data;
        capacity_ = new_size;
    }
    
    void push_back(const T& value)
    {
        if (size_ + 1 >= capacity_)
        {
            resize(capacity_ * 2);
        }
        
        // data_[size_++] = T(value);
        new(data_ + size_) T(value);
        size_++;
    }

    void push_back(T&& value)
    {
        if (size_ + 1 >= capacity_)
        {
            resize(capacity_ * 2);
        }
        
        // data_[size_++] = T(std::move(value));
        
        new(data_ + size_) T(std::move(value));
        size_++;
    }

    template<class... Args> 
    void emplace_back(Args&&... args)
    {
        if (size_ + 1 >= capacity_)
        {
            resize();
        }

        // data_[size_++] = new T(std::forward<Args>(args)...);
        new(data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }
    
    void pop_back()
    {
        assert(size_ >= 0); // , "Nothing to pop\n"
        
        data_[size_--].~T();
    }

    void swap(Dynamic_mem &other)
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
};

#endif // DYNAMIC_MEM_HPP
