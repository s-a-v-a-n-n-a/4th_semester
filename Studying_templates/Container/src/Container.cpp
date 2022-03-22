#include "Container.hpp"

template
<
    typename T,
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
T& Container<T, Size, Storage>::operator [] (const size_t index) 
{ 
    std::static_assert(index < size_, "Invalid index\n");
    
    return data(index); 
}

template
<
    typename T,
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
T& Container<T, Size, Storage>::front()
{
    std::static_assert(size_ > 0, "Invalid index\n");

    return data_[0];
}

template
<
    typename T,
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
T& Container<T, Size, Storage>::back()
{
    std::static_assert(size_ > 0, "Invalid index\n");
    
    return data_[size_ - 1];
}

//////////////////////////////////////////////////////////////////////////////////////

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
Container<bool, Size, Storage>::Container()
: Storage(), bools_amount(Size), wrapper()
{
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
bool& Container<bool, Size, Storage>::operator [] (const size_t index)
{
    std::static_assert(index < size_, "Invalid index\n");
    std::static_assert(index > 0, "Invalid index\n");
    
    return wrapper(index);
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
bool& Container<bool, Size, Storage>::front()
{
    wrapper.update(0);
    return wrapper;
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
bool& Container<bool, Size, Storage>::back()
{
    wrapper.update(bools_amount_ - 1);
    return wrapper;
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::resize(size_t new_size)
{
    Storage::resize(std::ceil((float)new_size / (float)sizeof(unsigned char)));
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::resize(size_t new_size, const bool& value)
{
    unsigned char propagated_value = 0;
    if (value)
        propagated_value = (unsigned char)(-1);

    size_t valid_size = std::ceil((float)new_size / (float)sizeof(unsigned char));

    Storage::resize(valid_size, propagated_value);
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::push_back(const bool& value)
{
    if (bools_amount_ % sizeof(unsigned char) < sizeof(unsigned char) - 1)
    {
        Storage::push_back(0);
    }

    wrapper.update(bools_amount_++); 
    wrapper = value;
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::push_back(bool&& value)
{
    std::static_assert(resizeable, "Data can't be resized\n");
    
    if (bools_amount_ % sizeof(unsigned char) == sizeof(unsigned char) - 1)
    {
        Storage::push_back(0);
    }

    wrapper.update(bools_amount_++); 
    wrapper = value;
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::emplace_back(bool arg)
{
    std::static_assert(resizeable, "Data can't be resized\n");
    
    push_back(arg);
}

template
<
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
void Container<bool, Size, Storage>::pop_back()
{    
    if (bools_amount_ % sizeof(unsigned char) == 0)
    {
        Storage::pop_back();
    }

    std::static_assert(bools_amount_ > 0, "Nothing to pop\n");

    bools_amount_--;
}
