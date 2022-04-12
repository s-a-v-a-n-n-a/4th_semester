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
class Container : public Storage<T>
{
private:
    typedef Storage<T> Base;

public:
    template <typename Iter_type>
    class Iterator
    {
    protected:
        long long index_;
        Container *array_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= Iter_type;
		using pointer			= Iter_type*;
		using reference			= Iter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Iterator() : index_(0), array_(nullptr) {}
        Iterator(Container *array, const long long index) 
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

        bool operator==(const Iterator<Iter_type> &other) const { return index_ == other.index_; }
        bool operator!=(const Iterator<Iter_type> &other) const { return index_ != other.index_; }
        bool operator<=(const Iterator<Iter_type> &other) const { return index_ <= other.index_; }
        bool operator>=(const Iterator<Iter_type> &other) const { return index_ >= other.index_; }
        bool operator<(const Iterator<Iter_type> &other) const { return index_ < other.index_; }
        bool operator>(const Iterator<Iter_type> &other) const { return index_ > other.index_; }
    };

    template <typename CIter_type>
    class Const_iterator
    {
    protected:
        long long index_;
        Container *array_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= CIter_type;
		using pointer			= CIter_type*;
		using reference			= CIter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Const_iterator() : index_(0), array_(nullptr) {}
        Const_iterator(Container *array, const long long index) 
        : index_(index),
          array_(array) {}
        Const_iterator(const Const_iterator &other)
        {
            index_ = other.index_;
            array_ = other.array_;
        }

        CIter_type const &operator*()
        {
            return (*array_)[index_];
        }

        CIter_type * const operator->() 
        {
            return &array_[0] + index_;
        }

        Const_iterator &operator++()
        {
            ++index_;

            return *this;
        }

        Const_iterator operator++(int)
        {
            Iterator copy(*this);
            ++index_;

            return copy;
        }

        Const_iterator &operator--()
        {
            --index_;

            return *this;
        }

        Const_iterator operator--(int)
        {
            Const_iterator copy(*this);
            --index_;

            return copy;
        }

        bool operator==(const Const_iterator<CIter_type> &other) const { return index_ == other.index_; }
        bool operator!=(const Const_iterator<CIter_type> &other) const { return index_ != other.index_; }
        bool operator<=(const Const_iterator<CIter_type> &other) const { return index_ <= other.index_; }
        bool operator>=(const Const_iterator<CIter_type> &other) const { return index_ >= other.index_; }
        bool operator<(const Const_iterator<CIter_type> &other) const { return index_ < other.index_; }
        bool operator>(const Const_iterator<CIter_type> &other) const { return index_ > other.index_; }
    };

    template <typename RIter_type>
    class Reversed_iterator
    {
    protected:
        long long index_;
        Container *array_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= RIter_type;
		using pointer			= RIter_type*;
		using reference			= RIter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Reversed_iterator() : index_(0), array_(nullptr) {}
        Reversed_iterator(Container *array, const long long index) 
        : index_(index),
          array_(array) {}
        Reversed_iterator(const Reversed_iterator &other)
        {
            index_ = other.index_;
            array_ = other.array_;
        }

        RIter_type &operator*()
        {
            return (*array_)[index_];
        }

        RIter_type *operator->() 
        {
            return &array_[0] + index_;
        }

        Reversed_iterator &operator++()
        {
            --index_;

            return *this;
        }

        Reversed_iterator operator++(int)
        {
            Reversed_iterator copy(*this);
            --index_;

            return copy;
        }

        Reversed_iterator &operator--()
        {
            ++index_;

            return *this;
        }

        Reversed_iterator operator--(int)
        {
            Reversed_iterator copy(*this);
            ++index_;

            return copy;
        }

        bool operator==(const Reversed_iterator<RIter_type> &other) const { return index_ == other.index_; }
        bool operator!=(const Reversed_iterator<RIter_type> &other) const { return index_ != other.index_; }
        bool operator<=(const Reversed_iterator<RIter_type> &other) const { return index_ >= other.index_; }
        bool operator>=(const Reversed_iterator<RIter_type> &other) const { return index_ <= other.index_; }
        bool operator<(const Reversed_iterator<RIter_type> &other) const { return index_ > other.index_; }
        bool operator>(const Reversed_iterator<RIter_type> &other) const { return index_ < other.index_; }
    };

    template <typename CRIter_type>
    class Const_reversed_iterator
    {
    protected:
        long long index_;
        Container *array_;

    public:
        using difference_type	= ptrdiff_t;
		using value_type		= CRIter_type;
		using pointer			= CRIter_type*;
		using reference			= CRIter_type&;
		using iterator_category	= std::bidirectional_iterator_tag;

        Const_reversed_iterator() : index_(0), array_(nullptr) {}
        Const_reversed_iterator(Container *array, const long long index) 
        : index_(index),
          array_(array) {}
        Const_reversed_iterator(const Const_reversed_iterator &other)
        {
            index_ = other.index_;
            array_ = other.array_;
        }

        CRIter_type const &operator*()
        {
            return (*array_)[index_];
        }

        CRIter_type * const operator->() 
        {
            return &array_[0] + index_;
        }

        Const_reversed_iterator &operator++()
        {
            --index_;

            return *this;
        }

        Const_reversed_iterator operator++(int)
        {
            Const_reversed_iterator copy(*this);
            --index_;

            return copy;
        }

        Const_reversed_iterator &operator--()
        {
            ++index_;

            return *this;
        }

        Const_reversed_iterator operator--(int)
        {
            Reversed_iterator copy(*this);
            ++index_;

            return copy;
        }

        bool operator==(const Const_reversed_iterator<CRIter_type> &other) const { return index_ == other.index_; }
        bool operator!=(const Const_reversed_iterator<CRIter_type> &other) const { return index_ != other.index_; }
        bool operator<=(const Const_reversed_iterator<CRIter_type> &other) const { return index_ >= other.index_; }
        bool operator>=(const Const_reversed_iterator<CRIter_type> &other) const { return index_ <= other.index_; }
        bool operator<(const Const_reversed_iterator<CRIter_type> &other) const { return index_ > other.index_; }
        bool operator>(const Const_reversed_iterator<CRIter_type> &other) const { return index_ < other.index_; }
    };

public:
    Container() : Base() {}
    Container(size_t amount, const T& initial_element) : Base(amount, initial_element) {}
    Container(std::initializer_list<T> list) : Base(list) {}

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
    // ------------ For iterator ------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Iterator<T> begin()
    {
        return Iterator<T>(this, 0);
    }

    Iterator<T> end()
    {
        return Iterator<T>(this, Base::size_);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const iterator ------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Const_iterator<T> cbegin()
    {
        return Const_iterator<T>(this, 0);
    }

    Const_iterator<T> cend()
    {
        return Const_iterator<T>(this, Base::size_);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For reversed iterator ---------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Reversed_iterator<T> rbegin()
    {
        return Reversed_iterator<T>(this, Base::size_ - 1);
    }

    Reversed_iterator<T> rend()
    {
        return Reversed_iterator<T>(this, -1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ For const reversed iterator ---------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Const_reversed_iterator<T> crbegin()
    {
        return Const_reversed_iterator<T>(this, Base::size_ - 1);
    }

    Const_reversed_iterator<T> crend()
    {
        return Const_reversed_iterator<T>(this, -1);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------------------------------------------------
// ---------------- Bool specialization -----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    // size_t Size,
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

        void operator= (const bool other)
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
    : Bool_base()
    {
        size_t list_size = list.size()/sizeof(unsigned char) + (size_t)(list.size() % sizeof(unsigned char) != 0);
        assert(list_size <= Bool_base::size_);

        size_t i = 0;
        for (auto idx = list.begin(); idx != list.end(); idx++, i++)
        {
            Bool_base::data(i) = idx;
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

    size_t size() const { return bools_amount_; }
    size_t capacity() const { return capacity() * sizeof(unsigned char); }
    // size_t max_size();
    // void shrink_to_fit(); 

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
        assert(Bool_base::resizeable_); // , "Data can't be resized\n"
        
        if (bools_amount_ % sizeof(unsigned char) == sizeof(unsigned char) - 1)
        {
            Bool_base::push_back((unsigned char)0);
        }

        wrapper.update(bools_amount_++); 
        wrapper = value;
    }

    void emplace_back(bool arg)
    {
        assert(Bool_base::resizeable); // , "Data can't be resized\n"
        
        push_back(arg);
    }
    
    void pop_back()
    {    
        assert(Bool_base::size_ > 0); // , "Nothing to pop\n"
        
        if (bools_amount_ % sizeof(unsigned char) == 0)
        {
            Bool_base::pop_back();
        }

        bools_amount_--;
    }
};

// TODO: how to make specialization for bools for static memory

#endif // CONTAINER_HPP
