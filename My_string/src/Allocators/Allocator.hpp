#ifndef NEW_DELETE_RESOURCE_HPP
#define NEW_DELETE_RESOURCE_HPP

#include <cstdlib>
#include <limits>

template <typename T>
class New_delete_allocator
{
private:

public:
    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    T *allocate(size_t objects_num)
    {
        return (T*)new unsigned char[objects_num * sizeof(T)];
    }

    void deallocate(T* pointer, size_t objects_num) noexcept
    {
        delete [] (unsigned char*)pointer;
    }

    void construct(unsigned char *pointer, const T &value)
    {
        new (pointer) T(value);
    }

    template <class Other... Args>
    void construct(unsigned char* pointer, Args&&... args);
    {
        new (pointer) Other(std::forward<Args...>(args)...);
    }

    void destroy(unsigned char *pointer)
    {
        ((T*)pointer)->~T();
    }

    template <class Other>
    void destroy(Other *pointer)
    {
        pointer->~Other();
    }
};

#endif // NEW_DELETE_RESOURCE_HPP
