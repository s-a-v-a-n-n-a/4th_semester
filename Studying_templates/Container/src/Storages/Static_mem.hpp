#ifndef STATIC_MEM_HPP
#define STATIC_MEM_HPP

#include <cstdio>
#include <cstdlib>

#include <cassert>
#include <stdexcept>

#include <utility>
#include <initializer_list>

template <typename T, size_t Size>
class Static_memory
{
protected:
    T data_[Size];

    const size_t size_;

    const bool resizeable_{false};

public: 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Constructors ------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Static_memory() : size_(Size) {}
    explicit Static_memory(std::initializer_list<T> list) : size_(Size)
    {
        if (list.size() > size_)
        {
            throw std::out_of_range("Wrong initializer list size\n");
        }

        size_t i = 0;
        for (auto idx = list.begin(); idx != list.end(); idx++, i++)
        {
            data_[i] = *idx;
        }
    }

    ~Static_memory()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i].~T();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Data --------------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    T &data(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Wrong index range\n");
        }

        return data_[index];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Size -------------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    [[nodiscard]] size_t get_capacity() const { return size_; }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Capacity ----------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] size_t capacity() const { return size(); }
    [[nodiscard]] size_t max_size() const { return size(); }
    void shrink_to_fit() 
    {
        assert(resizeable_); // , "Data can't be resized\n"
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Modifiers ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void clear()
    {
        assert(resizeable_);
    }

    void resize(size_t new_size)
    {
        assert(resizeable_); // , "Data can't be resized\n"
    }

    void resize(size_t new_size, const T &value)
    {
        assert(resizeable_); // , "Data can't be resized\n"
    }

    void push_back(const T &value)
    {
        assert(resizeable_);
    }

    void push_back(T &&value)
    {
        assert(resizeable_);
    }
    
    template<class... Args> 
    void emplace_back(Args&&... args)
    {
        assert(resizeable_);
    }

    void pop_back()
    {
        assert(resizeable_);
    }
    
    void swap(Static_memory<T, Size> &other)
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
