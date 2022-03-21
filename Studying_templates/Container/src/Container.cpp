#include "Container.hpp"

template
<
    typename T,
    size_t Size,
    template <typename Storage_type, size_t Storage_size> class Storage
>
const T& Container<T, Size, Storage>::operator [] (const size_t index) 
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
const bool Container<bool, Size, Storage>::operator [] (const size_t index)
{
    std::static_assert(index < size_, "Invalid index\n");
    std::static_assert(index > 0, "Invalid index\n");
    
    return data[index]
}
