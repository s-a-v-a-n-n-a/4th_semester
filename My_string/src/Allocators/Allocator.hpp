#ifndef NEW_DELETE_RESOURCE_HPP
#define NEW_DELETE_RESOURCE_HPP

#include <cstdlib>
#include <limits>

#include <stdexcept>

enum class New_param
{
    ZEROING = 0
};

void *operator new[](size_t size, New_param parameter)
{
    if (void *ptr = calloc(size, sizeof(unsigned char)))
    {
        return ptr;
    }
        
    throw std::bad_alloc{};
}

template <typename T>
class Zeroing_allocator
{
private:
    // Nothing

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Constructors ------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr Zeroing_allocator() noexcept
    {}

    constexpr Zeroing_allocator(const Zeroing_allocator &other) noexcept
    {}

    constexpr Zeroing_allocator(Zeroing_allocator &&other) noexcept
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Capacity ----------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- (De)allocation ----------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    T *allocate(size_t objects_num)
    {
        return (T*)new (New_param::ZEROING) unsigned char[objects_num * sizeof(T)];
    }

    void deallocate(T* pointer, size_t objects_num) noexcept
    {
        delete [] (unsigned char*)pointer;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- (De)construction --------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // void construct(unsigned char *pointer, const T &value)
    // {
    //     new (pointer) T(value);
    // }

    // template <classtype Other... Args>
    // void construct(unsigned char* pointer, Args&&... args);
    // {
    //     new (pointer) Other(std::forward<Args...>(args)...);
    // }

    // void destroy(unsigned char *pointer)
    // {
    //     ((T*)pointer)->~T();
    // }

    // template <class Other>
    // void destroy(Other *pointer)
    // {
    //     pointer->~Other();
    // }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // --------------------- Comparisons -------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool operator==(const Zeroing_allocator<T> &other)
    {
        return true;
    }

    bool operator!=(const Zeroing_allocator<T> &other)
    {
        return false;
    }
};

#endif // NEW_DELETE_RESOURCE_HPP
