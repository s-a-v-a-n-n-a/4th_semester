#ifndef STRATEGY_VIEW_HPP
#define STRATEGY_VIEW_HPP

#include <cstdlib>
#include <cassert>

template <typename Type, size_t Size>
class Strategy_view
{
private:
    const Type *buffer_;
    size_t size_;

public:
    Strategy_view() : buffer_(nullptr), size_(0) {}
    Strategy_view(Type const *buffer) : buffer_(buffer), size_(Size) {}

    Type &operator[](size_t index)
    {
        assert(buffer_);
        
        return buffer[index];
    }
};

#endif // STRATEGY_VIEW_HPP
