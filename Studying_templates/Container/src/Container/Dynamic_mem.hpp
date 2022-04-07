#ifndef DYNAMIC_MEM_HPP
#define DYNAMIC_MEM_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdint>

#include <stdexcept>
#include <new>

#include <utility>
#include <initializer_list>
#include <iterator>


template <typename T>
class Dynamic_mem
{
public:
    template <typename Iter_type>
    class Iterator
    {
    protected:
        long long index_;
        Iter_type *current_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= Iter_type;
		using pointer			= Iter_type*;
		using reference			= Iter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Iterator() : current_(nullptr), index_(0) {}
        Iterator(Iter_type *initial, const long long index) : index_(index), current_(initial) {}
        Iterator(const Iterator &other)
        {
            current_ = other.current_;
            index_ = other.index_;
        }

        Iter_type &operator*()
        {
            return *current_;
        }

        Iter_type *operator->() 
        {
            return current_;
        }

        Iterator &operator++()
        {
            ++current_;
            ++index_;

            return *this;
        }

        Iterator operator++(int tmp)
        {
            Iterator copy(*this);
            ++current_;
            ++index_;

            return copy;
        }

        Iterator &operator--()
        {
            --current_;
            --index_;

            return *this;
        }

        Iterator operator--(int tmp)
        {
            Iterator copy(*this);
            --current_;
            --index_;

            return copy;
        }

        bool operator==(const Iterator<Iter_type> &other) const
        {
            return index_ == other.index_;
        }
        bool operator!=(const Iterator<Iter_type> &other) const
        {
            return index_ != other.index_;
        }
        bool operator<=(const Iterator<Iter_type> &other) const
        {
            return index_ <= other.index_;
        }
        bool operator>=(const Iterator<Iter_type> &other) const
        {
            return index_ >= other.index_;
        }
        bool operator<(const Iterator<Iter_type> &other) const
        {
            return index_ < other.index_;
        }
        bool operator>(const Iterator<Iter_type> &other) const
        {
            return index_ > other.index_;
        }
    };

    template <typename RIter_type>
    class Reversed_iterator
    {
    protected:
        long long index_;
        RIter_type *current_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= RIter_type;
		using pointer			= RIter_type*;
		using reference			= RIter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Reversed_iterator() : current_(nullptr), index_(0) {}
        Reversed_iterator(RIter_type *initial, const long long index) : index_(index), current_(initial) {}
        Reversed_iterator(const Reversed_iterator &other)
        {
            current_ = other.current_;
            index_ = other.index_;
        }

        RIter_type &operator*()
        {
            return *current_;
        }

        RIter_type *operator->() 
        {
            return current_;
        }

        Reversed_iterator &operator++()
        {
            --current_;
            --index_;

            return *this;
        }

        Reversed_iterator operator++(int tmp)
        {
            Reversed_iterator copy(*this);
            --current_;
            --index_;

            return copy;
        }

        Reversed_iterator &operator--()
        {
            ++current_;
            ++index_;

            return *this;
        }

        Reversed_iterator operator--(int tmp)
        {
            Reversed_iterator copy(*this);
            ++current_;
            ++index_;

            return copy;
        }

        bool operator==(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ == other.index_;
        }
        bool operator!=(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ != other.index_;
        }
        bool operator<=(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ >= other.index_;
        }
        bool operator>=(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ <= other.index_;
        }
        bool operator<(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ > other.index_;
        }
        bool operator>(const Reversed_iterator<RIter_type> &other) const
        {
            return index_ < other.index_;
        }
    };

protected:
    T *data_;
    
    size_t size_;
    size_t capacity_;

    const bool resizeable_{true};

public:
    Dynamic_mem() : data_(0), size_(0), capacity_(0) {}

    Dynamic_mem(size_t amount, const T& initial_element) : size_(amount), capacity_(2 * amount)
    {
        data_ = (T*)(new unsigned char[capacity_ * sizeof(T)]);

        for (size_t i = 0; i < amount; i++)
        {
            new(data_ + i) T(initial_element);
        }
    }

    Dynamic_mem(std::initializer_list<T> list) : size_(list.size()), capacity_(2 * list.size())
    {
        data_ = (T*)(new unsigned char[capacity_ * sizeof(T)]);

        size_t j = 0;
        for (auto i = list.begin(); i != list.end(); i++, j++)
        {
            new(data_ + j) T(*i);
        }
    }

    ~Dynamic_mem()
    {
        if (data_) 
        {
            for (size_t i = 0; i < size_; ++i)
            {
                data_[i].~T();
            }

            delete [] data_;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Size --------------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    size_t get_capacity() const { return capacity_; }

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

    // ------------ Capacity ------------------------------------
    bool empty()                { return (size_ == 0); }
    size_t size()       const   { return size_; }
    size_t capacity()   const   { return get_capacity(); }
    size_t max_size()   const   { return SIZE_MAX; }
    
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

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Modifiers ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
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
        size_t new_capacity = new_size * 2;
        size_t size_to_copy = size_ < new_size ? size_ : new_size;
        
        T* new_data = (T*)(new unsigned char[new_capacity * sizeof(T)]);
        
        for (size_t idx = 0; idx < size_to_copy; ++idx) 
        {
            new(new_data + idx) T(std::move(data_[idx]));
        }

        if (new_size < size_)
        {
            for (size_t idx = size_; idx < new_size; ++idx)
            {
                data_[idx].~T();
            }
        }

        delete [] data_;

        data_ = new_data;
        size_ = new_size;
        capacity_ = new_capacity;
    }

    void resize(size_t new_size, const T& value)
    {
        size_t new_capacity = new_size * 2;
        size_t size_to_copy = size_ < new_size ? size_ : new_size;
        
        T* new_data = (T*)(new unsigned char[new_capacity * sizeof(T)]);
        for (size_t idx = 0; idx < size_to_copy; ++idx) 
        {
            new(new_data + idx) T(std::move(data_[idx]));
        }
        for (size_t idx = size_to_copy; idx < new_size; ++idx)
        {
            new(new_data + idx) T(value);
        }

        if (new_size < size_)
        {
            for (size_t idx = size_; idx < new_size; ++idx)
            {
                data_[idx].~T();
            }
        }

        delete [] data_;

        data_ = new_data;
        size_ = new_size;
        capacity_ = new_capacity;
    }
    
    void push_back(const T& value)
    {
        if (size_ + 1 >= capacity_)
        {
            resize(capacity_ * 2);
        }
        
        new(data_ + size_) T(value);
        
        size_++;
    }

    void push_back(T&& value)
    {
        if (size_ + 1 >= capacity_)
        {
            resize(capacity_ * 2);
        }
        
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

        new(data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }
    
    void pop_back()
    {
        if (size_ == 0)
        {
            throw std::out_of_range("Nothing to pop\n");
        }
        
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

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For iterator ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Iterator<T> begin()
    {
        return Iterator<T>(data_, 0);
    }

    Iterator<T> end()
    {
        return Iterator<T>(data_ + size_, size_);
    }

    Reversed_iterator<T> rbegin()
    {
        return Reversed_iterator<T>(data_ + size_ - 1, size_ - 1);
    }

    Reversed_iterator<T> rend()
    {
        return Reversed_iterator<T>(data_ - 1, -1);
    }
};

#endif // DYNAMIC_MEM_HPP
