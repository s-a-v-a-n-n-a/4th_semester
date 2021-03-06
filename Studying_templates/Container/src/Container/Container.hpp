#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstdio>
#include <initializer_list>
#include <cassert>
#include <cmath>

#include <stdexcept>
#include <iterator>

template
<
    typename T,
    template <typename Storage_type> class Storage
>
class Container : protected Storage<T>
{
private:
    typedef Storage<T> Base;

public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------------------- Constructors -----------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Container() : Base() {}
    Container(size_t amount, const T& initial_element) : Base(amount, initial_element) {}
    Container(std::initializer_list<T> list) : Base(list) {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------------------- Capacity ---------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool empty() const { return (Base::size_ == 0); }

    using Base::size;
    using Base::capacity;
    using Base::max_size;
    using Base::shrink_to_fit;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // -------------------------Element access-----------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr T &at(size_t position)
    {
        if (position > Base::size_)
        {
            throw std::out_of_range("Wrong position range\n");
        }

        return Base::data(position);
    }
    
    constexpr T &front()
    {
        if (Base::size_ == 0)
        {
            throw std::out_of_range("No elements available\n");
        }

        return Base::data(0);
    }
    
    constexpr T &back()
    {
        if (Base::size_ == 0)
        {
            throw std::out_of_range("No elements available\n");
        }
        
        return Base::data(Storage<bool>::size_ - 1);
    }

    T &operator[] (const size_t index)
    { 
        if (index >= Base::size_)
        {
            throw std::out_of_range("Array index out of range"); 
        }
        
        return Base::data(index); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Modifiers ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    using Base::clear;
    using Base::resize;
    using Base::swap;

    using Base::push_back;
    using Base::emplace_back;
    using Base::pop_back;

public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------------------- Iterators --------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template 
    <
        typename Iter_type,
        typename Container_type
    >
    class Iterator
    {
    protected:
        long long index_;
        Container_type *array_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= Iter_type;
		using pointer			= Iter_type*;
		using reference			= Iter_type&;
		using iterator_category	= std::random_access_iterator_tag;

        Iterator() : index_(0), array_(nullptr) {}
        Iterator(Container_type *array, const long long index) 
        : index_(index),
          array_(array) {}
        Iterator(const Iterator &other)
        {
            index_ = other.index_;
            array_ = other.array_;
        }

        Iter_type &operator*()
        {
            return (*array_)[index_];
        }

        Iter_type *operator->() 
        {
            return &array_[0] + index_;
        }

        Iterator &operator++()
        {
            ++index_;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator copy(*this);
            ++index_;

            return copy;
        }

        Iterator &operator--()
        {
            --index_;

            return *this;
        }

        Iterator operator--(int)
        {
            Iterator copy(*this);
            --index_;

            return copy;
        }

        Iterator &operator+=(const ssize_t adding)
        {
            index_ += adding;

            return *this;
        }

        Iterator operator+(const ssize_t adding)
        {
            Iterator copy(*this);
            
            copy.index_ += adding;

            return copy;
        }

        Iterator &operator-=(const ssize_t minus)
        {
            index_ -= minus;

            return *this;
        }

        Iterator operator-(const ssize_t minus)
        {
            Iterator copy(*this);
            
            copy.index_ -= minus;

            return copy;
        }

        ssize_t operator+(const Iterator &other)
        {
            return index_ + other.index_;
        }

        ssize_t operator-(const Iterator &other)
        {
            return index_ - other.index_;
        }

        bool operator==(const Iterator<Iter_type, Container_type> &other) const { return index_ == other.index_; }
        bool operator!=(const Iterator<Iter_type, Container_type> &other) const { return index_ != other.index_; }
        bool operator<=(const Iterator<Iter_type, Container_type> &other) const { return index_ <= other.index_; }
        bool operator>=(const Iterator<Iter_type, Container_type> &other) const { return index_ >= other.index_; }
        bool operator<(const Iterator<Iter_type, Container_type> &other) const { return index_ < other.index_; }
        bool operator>(const Iterator<Iter_type, Container_type> &other) const { return index_ > other.index_; }
    };

    using reverse_iterator       = std::reverse_iterator<Iterator<T, Container>>;
    using const_iterator         = Iterator<T, const Container>;
    using const_reverse_iterator = std::reverse_iterator<Iterator<T, const Container>>;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For iterator ------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Iterator<T, Container> begin()
    {
        return Iterator<T, Container>(this, 0);
    }

    Iterator<T, Container> end()
    {
        return Iterator<T, Container>(this, Base::size_);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const iterator ------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    const_iterator cbegin()
    {
        return const_iterator(begin());
    }

    const_iterator cend()
    {
        return const_iterator(end());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For reversed iterator ---------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const reversed iterator ---------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    const_reverse_iterator crbegin()
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crend()
    {
        return const_reverse_iterator(begin());
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------------------------------------------------
// ---------------- Bool specialization -----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    template <typename Storage_type> class Storage
>
class Container<bool, Storage> : public Storage<unsigned char>
{
private:
    using Bool_base = Storage<unsigned char>;

    size_t bools_amount_;

    struct Bool_wrapper
    {
        Container<bool, Storage> *source_;
        
        size_t index_;
        unsigned char bit_;

        bool value_;
    
        Bool_wrapper() = delete;
        
        Bool_wrapper(Container<bool, Storage> *source) : source_(source)
        {
            update(0);
        }
        
        explicit Bool_wrapper(size_t virtual_index)
        {
            update(virtual_index);
        }
        
        operator bool() const { return value_; }

        void update(size_t virtual_index)
        {
            index_ = virtual_index / sizeof(unsigned char);
            bit_ = virtual_index % sizeof(unsigned char);
            value_ = (source_->get_value(index_) << bit_) & 1;
        }

        void operator=(const bool other)
        {
            value_ = other;

            source_->set_value(index_, (unsigned char)(source_->get_value(index_) & ~(1 << bit_)));
            source_->set_value(index_, (unsigned char)(source_->get_value(index_) | (value_ << bit_)));
        }
    };

    Bool_wrapper wrapper;

public:
    Container() : Bool_base(), bools_amount_(0), wrapper(this) {}
    Container(size_t amount, const bool value) 
    : Bool_base(2 * amount / sizeof(unsigned char) + 
               (size_t)(2 * amount % sizeof(unsigned char) != 0), value), 
      wrapper(this)
    {
        size_t new_size = 2 * amount;
        bools_amount_ = new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0);
    }

    Container(std::initializer_list<bool> list)
    : Bool_base(list.size()/sizeof(unsigned char) + (size_t)(list.size() % sizeof(unsigned char) != 0), 0), 
      bools_amount_(list.size()), 
      wrapper(this)
    {
        size_t list_size = list.size()/sizeof(unsigned char) + (size_t)(list.size() % sizeof(unsigned char) != 0);
        assert(list_size <= Bool_base::size_);

        unsigned char value = 0;
        size_t i = 0;
        size_t char_chunk = 0;
        for (auto idx = list.begin(); idx != list.end(); idx++, i++)
        {
            value |= ((int)(*idx) << (i % sizeof(unsigned char)));
            if (i % sizeof(unsigned char) == sizeof(unsigned char) - 1)
            {
                Bool_base::data(char_chunk) = value;
                value = 0;
                ++char_chunk;
            }
        }

        if (i % sizeof(unsigned char) < sizeof(unsigned char) - 1)
        {
            Bool_base::data(char_chunk) = value;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Elements access ---------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void set_value(const size_t index, const unsigned char value)
    {
        Bool_base::data(index) = value;
    }

    unsigned char get_value(const size_t index)
    {
        return Bool_base::data(index);
    }

    bool &front()
    {
        wrapper.update(0);
        return wrapper;
    }
    
    bool &back()
    {
        wrapper.update(bools_amount_ - 1);
        return wrapper;
    }

    Bool_wrapper &operator[] (const size_t index)
    {   
        wrapper.update(index);
        return wrapper;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Capacity ----------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    size_t size()     const { return bools_amount_; }
    size_t capacity() const { return capacity() * sizeof(unsigned char); }
    size_t max_size() const { return SIZE_MAX; }
    void shrink_to_fit()
    {
        Bool_base::shrink_to_fit(bools_amount_ / sizeof(unsigned char));
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Modifiers ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void resize(size_t new_size)
    {
        size_t new_size_compressed = new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0);
        Bool_base::resize(new_size_compressed);
    }

    void resize(size_t new_size, const bool& value)
    {        
        unsigned char propagated_value = 0;
        if (value)
            propagated_value = (unsigned char)(-1);

        size_t new_size_compressed = std::ceil(new_size / sizeof(unsigned char) + (size_t)(new_size % sizeof(unsigned char) != 0));

        Bool_base::resize(new_size_compressed, propagated_value);
    }

    constexpr Bool_wrapper &at(size_t position)
    {
        if (position > bools_amount_)
        {
            throw std::out_of_range("Wrong position range\n");
        }
        
        return Bool_base::data_[position];
    }

    void push_back(const bool& value)
    {
        if (bools_amount_ % sizeof(unsigned char) < sizeof(unsigned char) - 1)
        {
            Bool_base::push_back(0);
        }

        wrapper.update(bools_amount_++); 
        wrapper = value;
    }

    void push_back(bool&& value)
    {
        assert(Bool_base::resizeable_); // Data can't be resized
        
        if (bools_amount_ % sizeof(unsigned char) == sizeof(unsigned char) - 1)
        {
            Bool_base::push_back((unsigned char)0);
        }

        wrapper.update(bools_amount_++); 
        wrapper = value;
    }

    void emplace_back(bool arg)
    {
        assert(Bool_base::resizeable); // Data can't be resized
        
        push_back(arg);
    }
    
    void pop_back()
    {    
        assert(Bool_base::resizeable); // Data can't be resized
        
        if (bools_amount_ % sizeof(unsigned char) == 0)
        {
            Bool_base::pop_back();
        }

        bools_amount_--;
    }
};

#endif // CONTAINER_HPP
