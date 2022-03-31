#ifndef CHUNCKED_MEM
#define CHUNCKED_MEM

template <typename T>
class Chuncked_mem
{
protected:
    T **data_;
    
    size_t size_;
    size_t capacity_;

    const bool resizeable_{true};

public:
    Chuncked_mem();
    Chuncked_mem(size_t amount, const T &initial_element);
    Chuncked_mem(std::initializer_list<T> list);
};

#endif // CHUNCKED_MEM
