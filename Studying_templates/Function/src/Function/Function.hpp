#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cstdio>
#include <stdexcept>
#include <functional>

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
        helper_ = new Callable<Functor_type, Return_type, Arguments...>(my_forward<Functor_type>(functor));
    }

    Function(const Function &other)
    : helper_((Callable_base<Return_type, Arguments...>*)other.helper_->get_copy())
    {}

    Function(Function &&other)
    : helper_(nullptr)
    {
        std::swap(helper_, other.helper_);
    }

    ~Function()
    {
        delete_helper();
    }

    Function &operator= (const Function &other)
    {
        if (&other == this) 
        {
            return *this;
        }

        delete_helper();
        
        helper_ = std::move((Callable_base<Return_type, Arguments...>*)other.helper_.get_copy());

        return *this;
    }

    Function &operator= (Function &&other)
    {
        if (&other == this) 
        {
            return *this;
        }
    
        std::swap(helper_, other.helper_);

        return *this;
    }

    void swap(Function &other) noexcept
    {
        std::swap(helper_, other.helper_);
    }

    template <typename Other_functor_type>
    void assign(Other_functor_type &&functor)
    {
        delete_helper();

        helper_ = new Callable<Other_functor_type, Return_type, Arguments...>(my_forward<Other_functor_type>(functor));
    }

    Return_type operator() (Arguments... args) const
    {
        if (!helper_)
        {
            throw std::bad_function_call();
        }        
        
        return (*helper_)(my_forward<Arguments>(args)...);
    }

    explicit operator bool()
    {
        return (helper_ != nullptr);
    }

    const std::type_info &taret_type() const noexcept
    {
        if (!helper_)
        {
            return typeid(void);
        }

        return helper_->target_type();
    }

    template <typename Other_type>
    Other_type* target() noexcept
    {
        if (taret_type() == typeid(Other_type))
        {
            return (Other_type*)(helper_->get_functor());
        }

        return nullptr;
    }

    template <class Other_type>
    const Other_type* target() const noexcept
    {
        if (taret_type() == typeid(Other_type))
        {
            return (Other_type*)(helper_->get_functor());
        }

        return nullptr;
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
    typename Return_type, typename ...Arguments \
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
