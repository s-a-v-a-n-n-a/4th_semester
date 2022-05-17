#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cstdio>
#include <stdexcept>

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
    Function(Functor_type &&functor)
    {
        // printf("Function: constructor from functor called\n");
        helper_ = new Callable<Functor_type, Return_type, Arguments...>(functor);
    }

    Function(const Function &other)
    : helper_(nullptr)
    {
        *this = Function(*other.helper_);
        // printf("Function: copy constructor called\n");
    }

    Function(Function &&other)
    : helper_(std::move(other.helper_))
    {}

    ~Function()
    {
        delete_helper();
    }

    Return_type operator() (Arguments... args) const
    {
        if (!helper_)
        {
            throw std::bad_function_call();
        }        
        // Be careful with my_forward
        return (*helper_)(my_forward<Arguments>(args)...);
    }

    Function &operator= (const Function &other)
    {
        delete_helper();
        
        helper_ = other.helper_;

        return *this;
    }

    Function &operator= (Function &&other)
    {
        delete_helper();
        
        helper_ = std::move(other.helper_);

        return *this;
    }

private:
    void delete_helper()
    {
        if (helper_)
        {
            delete helper_;
        }
        helper_ = nullptr;
    }

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------ For deduction -----------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Return_type, typename ... Arguments>
Function(Return_type (*)(Arguments...)) -> Function<Return_type (Arguments...)>;

namespace detail
{

template <typename Class>
struct Deduction_for_function;

#define DEDUCTION_FOR_FUNCTION_HELPER(modifiers) \
template \
< \
    typename Class, \
    typename Return_type, typename ... Arguments \
> \
struct Deduction_for_function<Return_type (Class::*)(Arguments...) modifiers> \
{ \
    using type = Return_type (Arguments...); \
}; \

DEDUCTION_FOR_FUNCTION_HELPER()
DEDUCTION_FOR_FUNCTION_HELPER(&)
DEDUCTION_FOR_FUNCTION_HELPER(&&)

DEDUCTION_FOR_FUNCTION_HELPER(const)
DEDUCTION_FOR_FUNCTION_HELPER(const &)
DEDUCTION_FOR_FUNCTION_HELPER(const &&)

DEDUCTION_FOR_FUNCTION_HELPER(noexcept)
DEDUCTION_FOR_FUNCTION_HELPER(& noexcept)
DEDUCTION_FOR_FUNCTION_HELPER(&& noexcept)

DEDUCTION_FOR_FUNCTION_HELPER(const noexcept)
DEDUCTION_FOR_FUNCTION_HELPER(const & noexcept)
DEDUCTION_FOR_FUNCTION_HELPER(const && noexcept)

}

template <typename Class>
Function(Class cls) -> Function<typename detail::Deduction_for_function<decltype(&Class::operator())>::type>;

#endif // FUNCTION_HPP
