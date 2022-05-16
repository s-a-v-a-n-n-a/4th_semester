#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Callable.hpp"

template <typename Type>
class Function;

template <typename Return_type, typename... Arguments>
class Function <Return_type (Arguments...)>
{
private:
    Callable_base<Return_type, Arguments...> *helper_;

public:
    Function() : helper_(nullptr)
    {}

    template <typename Functor_type>
    Function(Functor_type functor)
    {
        helper_ = new Callable<Functor_type, Return_type, Arguments...>(functor);
    }

    ~Function()
    {
        if (helper_)
        {
            delete helper_;
        }
    }

    Return_type operator() (Arguments... args)
    {
        // Be careful with my_forward
        return helper_->operator()(my_forward<Arguments>(args)...);
    }
};

#endif // FUNCTION_HPP
