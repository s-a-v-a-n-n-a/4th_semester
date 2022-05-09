#ifndef SHARED_PTR_ANNA_2022_HPP
#define SHARED_PTR_ANNA_2022_HPP

#include <cstdlib>

#include <cassert>

template <typename Type>
class Shared_data
{
public:
    Type data_;
    mutable size_t counter_;

    explicit Shared_data(Type &&data)
    : data_(std::move(data)), counter_(0)
    {}

    void add_pointers(size_t amount = 1)
    {
        counter_ += amount;
    }

    void remove_pointers(size_t amount = 1)
    {
        assert(counter_ >= amount);

        counter_ -= amount;
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
        object_->increase_pointers();
    }

    explicit Shared_ptr_cut(Shared_ptr_cut &other)
    : object_(other.object_)
    {
        object_->increase_pointers();
    }

    explicit Shared_ptr_cut(Shared_ptr_cut &&other)
    : object_(other.object_)
    {
        other.object_ = nullptr;
    }

    ~Shared_ptr_cut()
    {
        object_->remove_pointers();
    }

    Type &operator*()
    {
        return object_->data_;
    }

    Type *operator->()
    {
        return &(object_->data_);
    }
};

#endif // SHARED_PTR_ANNA_2022_HPP
