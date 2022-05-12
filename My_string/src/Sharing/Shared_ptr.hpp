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

    ~Shared_data()
    {
        if (counter_ == 0)
        {
            delete this;
        }
    }

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

template <typename Type>
class Shared_ptr_cut
{
private:
    Shared_data<Type> *object_;

public:
    Shared_ptr_cut()
    : object_(nullptr)
    {}

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

    ~Shared_ptr_cut()
    {
        if (object_)
        {
            object_->remove_pointers();
        }
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
