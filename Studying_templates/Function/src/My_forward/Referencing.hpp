#ifndef REFERENCING_HPP
#define REFERENCING_HPP

template<class T>
struct unreferenced_type
{
    typedef T type;
};

template<class T>
struct unreferenced_type<T&>
{
    typedef T type;
};

template<class T>
struct unreferenced_type<T&&>
{
    typedef T type;
};

#endif // REFERENCING_HPP
