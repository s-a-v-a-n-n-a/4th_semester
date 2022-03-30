#ifndef NO_DEFAULT_CONSTRUCTOR_HPP
#define NO_DEFAULT_CONSTRUCTOR_HPP

class No_default_constructor
{
private:
    int value_;

public:
    No_default_constructor() = delete;
    No_default_constructor(int value)
    : value_(value)
    {
    }
};

#endif // NO_DEFAULT_CONSTRUCTOR_HPP
