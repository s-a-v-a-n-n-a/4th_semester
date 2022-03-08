#ifndef MY_MOVE_HPP
#define MY_MOVE_HPP

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

template<class T>
typename unreferenced_type<T>::type&& my_move(T&& argument)
{
    return (static_cast<typename unreferenced_type<T>::type&&>(argument));
}

#endif // MY_MOVE_HPP
