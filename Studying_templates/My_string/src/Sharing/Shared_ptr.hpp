#ifndef SHARED_PTR_ANNA_2022_HPP
#define SHARED_PTR_ANNA_2022_HPP

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <cassert>

template <typename Type>
class Shared_data
{
private:
    void print_state()
    {
        std::cout << "Current pointers amount is " << counter_ << ".\n";
    }

public:
    Type data_;
    mutable size_t counter_;

    explicit Shared_data(Type &&data)
    : data_(std::move(data)), counter_(0)
    {}

    void add_pointers(size_t amount = 1)
    {
        counter_ += amount;
        print_state();
    }

    void remove_pointers(size_t amount = 1)
    {
        assert(counter_ >= amount);

        counter_ -= amount;
        print_state();
    }

    bool is_unused()
    {
        return (counter_ == 0);
    }
};

template 
<
    typename Type,
    template <typename Allocator_type> class Allocator
>
class Shared_ptr_cut
{
private:
    Allocator<Shared_data<Type>> shared_data_allocator_{};
    
    Shared_data<Type> *object_;

public:
    Shared_ptr_cut()
    : object_(nullptr)
    {}

    explicit Shared_ptr_cut(Type *content)
    {
        object_ = shared_data_allocator_.allocate(1);
        new (object_) Shared_data<Type>(std::move(*content));

        object_->add_pointers();
    }

    explicit Shared_ptr_cut(Shared_data<Type> *object)
    : object_(object)
    {
        object_->add_pointers();
    }

    explicit Shared_ptr_cut(const Shared_ptr_cut &other)
    : object_(other.object_)
    {
        object_->add_pointers();
    }

    explicit Shared_ptr_cut(Shared_ptr_cut &&other)
    : object_(other.object_)
    {
        other.object_ = nullptr;
    }

    ~Shared_ptr_cut()
    {
        if (!object_)
        {
            return;
        }
        
        object_->remove_pointers();

        if (object_->is_unused())
        {
            object_->~Shared_data<Type>();
            shared_data_allocator_.deallocate(object_, 1);
        }
    }

    constexpr Shared_ptr_cut &operator=(const Shared_ptr_cut &other)
    {
        object_ = other.object_;
        object_->add_pointers();

        return *this;
    }

    constexpr Shared_ptr_cut &operator=(Shared_ptr_cut &&other)
    {
        object_ = other.object_;
        other.object_ = nullptr;

        return *this;
    }

    Type &operator*()
    {
        return object_->data_;
    }

    Type &operator*() const
    {
        return object_->data_;
    }

    Type *operator->()
    {
        return &(object_->data_);
    }

    Type *operator->() const
    {
        return &(object_->data_);
    }
};

#endif // SHARED_PTR_ANNA_2022_HPP
