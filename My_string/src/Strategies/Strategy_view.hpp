#ifndef STRATEGY_VIEW_HPP
#define STRATEGY_VIEW_HPP

#include <cstdlib>
#include <cassert>

template <typename CharType, size_t Size>
class Strategy_view
{
private:
    const CharType *buffer_;
    size_t size_;

public:
    Strategy_view() : buffer_(nullptr), size_(0) {}
    Strategy_view(Type const *buffer) : buffer_(buffer), size_(Size) {}

    CharType *data() 
    {
        return buffer_;
    }

    CharType &operator[](size_t index)
    {
        assert(buffer_);
        
        return buffer[index];
    }
};

#endif // STRATEGY_VIEW_HPP
