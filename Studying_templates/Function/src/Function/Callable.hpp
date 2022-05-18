#ifndef CALLABLE_BASE_HPP
#define CALLABLE_BASE_HPP

#include <typeinfo>

#include "../My_forward/My_forwarding.hpp"

template <typename Return_type, typename... Arguments>
class Callable_base
{
public:
    virtual ~Callable_base() 
    {}

    virtual Return_type operator() (Arguments...) = 0;

    virtual void *get_copy() = 0;
    virtual const std::type_info &target_type() = 0;

    virtual void *get_functor() const = 0;
};

template <typename Functor_type, typename Return_type, typename... Arguments>
class Callable : public Callable_base <Return_type, Arguments...>
{
private:
    Functor_type functor_;
public:
    Callable(Functor_type functor)
    : functor_(functor)
    {}

    virtual Return_type operator() (Arguments...args) override
    {
        // Be careful with my_forward
        return functor_(my_forward<Arguments>(args)...);
    }

    virtual void *get_copy() override
    {
        return new Callable(functor_);
    }

    virtual const std::type_info &target_type() override
    {
        return typeid(Functor_type);
    }

    virtual void *get_functor() const override
    {
        return (void*)(&functor_);
    }
};

#endif // CALLABLE_BASE_HPP