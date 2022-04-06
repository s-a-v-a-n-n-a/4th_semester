#ifndef CHUNCKED_MEM
#define CHUNCKED_MEM

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdint>

#include <stdexcept>

#include <utility>

#include <initializer_list>

#include <new>

template <typename T, size_t Chunk_size>
class Chunked_memory
{
protected:
    // template <typename T, size_t Chunk_size>
    // class Chunk
    // {
    // protected:        
    //     T *data_;

    //     size_t size_;

    //     bool has_initial_element_;
    //     T initial_element_;
    // public:
    //     Chunk()
    //     : data_(nullptr), size_(Chunk_size), has_initial_element(false) {}

    //     Chunk(const T &initial_element)
    //     : data_(nullptr), size_(Chunk_size), has_initial_element_(true), initial_element_(initial_element)
    //     {
    //     }

    //     T& operator[] (size_t index) 
    //     {
    //         if (!data_)
    //         {
    //             data_ = new unsigned char[size_ * sizeof(T)];
    //             if (has_initial_element_)
    //             {
    //                 for (size_t idx = 0; idx < size_; ++idx)
    //                 {
    //                     new(data_ + idx) T(initial_element_);
    //                 }
    //             }
    //         }
    //         return data_[index];
    //     }

    //     void operator= (const T& other)
    //     {
            
    //     }
    // };

protected:
    T **data_;
    
    size_t chunk_size_;
    
    size_t size_;
    size_t capacity_;

    const bool resizeable_{true};

    bool with_initial_element_;
    T initial_element_;

public:
    Chunked_memory()
    : data_(nullptr), 
      chunk_size_(Chunk_size), 
      size_(0), 
      capacity_(0) {}

    Chunked_memory(size_t amount, const T &initial_element)
    : data_(nullptr), 
      chunk_size_(Chunk_size), 
      size_(amount), 
      capacity_(2 * amount / chunk_size_ + (2 * amount % chunk_size_ != 0 )), 
      with_initial_element_(true), 
      initial_element_(initial_element)
    {}

    Chunked_memory(std::initializer_list<T> list)
    : data_(nullptr), 
      chunk_size_(Chunk_size), 
      size_(list.size()), 
      capacity_(2 * size_ / chunk_size_ + (2 * size_ % chunk_size_ != 0 )), 
      with_initial_element_(false)
    {
        size_t chunk_amount = capacity_ / chunk_size_;

        data_ = new T*[chunk_amount];
        
        size_t current_idx = 0;
        try
        {
            for (auto element = list.begin(); element != list.end(); element++, current_idx++)
            {
                if (current_idx % chunk_size_ == 0)
                {
                    data_[current_idx / chunk_size_] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
                }

                new(data_ + current_idx / chunk_size_) T(*element);
            }
        }
        catch(const std::exception& exception)
        {
            for (long long idx = current_idx; idx >= 0; --idx)
            {
                data_[idx / chunk_size_][idx % chunk_size_].~T();
                
                if (idx % chunk_size_ == 0)
                    delete data_[idx / chunk_size_];   
            }

            throw;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Data --------------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    T &data(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Wrong index range\n");
        }

        if (!data_)
        {
            data_ = new T*[capacity_];
            for (size_t idx = 0; idx < capacity_; ++idx)
            {
                data_[idx] = nullptr;
            }
        }
        
        size_t chunk_num = index / chunk_size_;

        if (data_[chunk_num] == nullptr)
        {
            data_[chunk_num] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
            if (with_initial_element_)
            {
                for (size_t idx = 0; idx < chunk_size_; ++idx)
                {
                    new(data_[chunk_num] + idx) T(initial_element_);
                }
            }
            else
            {
                assert(with_initial_element_);
            }
        }

        return data_[chunk_num][index % chunk_size_];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Capacity ----------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    bool   empty()              { return (size_ == 0); }
    size_t size()     const     { return size_; }
    size_t capacity() const     { return capacity_; }
    
    void shrink_to_fit()
    {
        size_t used_chunks_amount = size_ / chunk_size_ + (size_ % chunk_size_ != 0);
        size_t real_chunks_amount = capacity_ / chunk_size_;
        if (real_chunks_amount > used_chunks_amount)
        {
            for (long long idx = real_chunks_amount; idx > used_chunks_amount; --idx)
            {
                if (data_[idx])
                {
                    // должно хватать, т.к при любом удалении элемента вызывается деструктор
                    delete data_[idx];
                }
            }
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Modifiers ---------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void clear()
    {
        size_t chunks_amount = capacity_ / chunk_size_;

        for (size_t idx = 0; idx < chunks_amount; ++idx)
        {
            if (data_[idx] != nullptr)
            {
                for (size_t chunk_idx = 0; chunk_idx < chunk_size_; ++chunk_idx)
                {
                    data_[idx][chunk_idx].~T();
                }
            }
        }

        size_ = 0;
    } 

    // TODO: resize downside
    void resize(size_t new_size)
    {        
        size_t new_capacity = new_size / chunk_size_ + (new_size % chunk_size_ != 0);

        if (!data_)
        {
            capacity_ = new_capacity;
            size_     = new_size;
            return;
        }

        T** new_data = new T*[new_capacity];
        
        size_t old_chunks_amount = size_ / chunk_size_ + (size_ % chunk_size_ != 0);

        size_t chunks_to_copy = old_chunks_amount;
        bool downside = false;
        if (old_chunks_amount >= new_capacity)
        {
            downside = true;
            chunks_to_copy = new_capacity;
        }

        if (!downside)
        {
            for (size_t idx = capacity_ + 1; idx < new_capacity; ++idx)
            {
                new_data[idx] = nullptr;
            }
        }
            
        for (size_t idx = 0; idx < chunks_to_copy; ++idx)
        {
            if (data_[idx] != nullptr)
            {
                new_data[idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
                for (size_t chunk_idx = 0; chunk_idx < chunk_size_; ++chunk_idx)
                {
                    if (chunk_size_ * idx + chunk_idx >= size_)
                    {
                        break;
                    }

                    new(new_data[idx] + chunk_idx) T(std::move(data_[idx][chunk_idx]));
                }
            }
            else
            {
                new_data[idx] = nullptr;
            }
        }

        if (downside)
        {
            for (size_t idx = new_capacity; idx < old_chunks_amount; ++idx)
            {
                if (data_[idx] != nullptr)
                {
                    size_t to_start = idx == old_chunks_amount ? size_ % chunk_size_ : 0;
                    for (size_t chunk_idx = to_start; chunk_idx < chunk_size_; ++chunk_idx)
                    {
                        data_[idx][chunk_idx].~T();
                    }
                }
            }
        }

        // delete [] data_;
        std::swap(data_, new_data);

        delete [] new_data;
        // data_     = new_data;
        capacity_ = new_capacity;
        size_     = new_size;
    }

    void resize(size_t new_size, const T& value)
    {
        size_t new_capacity = new_size / chunk_size_ + ((new_size) % chunk_size_ != 0);

        if (!data_)
        {
            capacity_ = new_capacity;
            size_     = new_size;
            return;
        }

        T** new_data = new T*[new_capacity];
        
        size_t old_chunks_amount = size_ / chunk_size_ + (size_ % chunk_size_ != 0);
        size_t chunks_to_copy = old_chunks_amount;
        bool downside = false;
        if (old_chunks_amount >= new_capacity)
        {
            downside = true;
            chunks_to_copy = new_capacity;
        }

        if (!downside)
        {
            for (size_t idx = capacity_ / chunk_size_ + 1; idx < new_capacity; ++idx)
            {
                new_data[idx] = nullptr;
            }
        }

        for (size_t idx = 0; idx < old_chunks_amount; ++idx)
        {
            if (data_[idx] != nullptr)
            {
                new_data[idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
                for (size_t chunk_idx = 0; chunk_idx < chunk_size_; ++chunk_idx)
                {
                    if (chunk_size_ * idx + chunk_idx >= size_)
                    {
                        new(new_data[idx] + chunk_idx) T(value);
                    }
                    else
                    {
                        new(new_data[idx] + chunk_idx) T(std::move(data_[idx][chunk_idx]));
                    }
                }
            }
            else if (with_initial_element_)
            {
                new_data[idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
                for (size_t chunk_idx = 0; chunk_idx < chunk_size_; ++chunk_idx)
                {
                    if (chunk_idx * idx >= size_)
                    {
                        new(new_data[idx] + chunk_idx) T(value);
                    }
                    else
                    {
                        new(new_data[idx] + chunk_idx) T(initial_element_);
                    }
                }
            }
            else
            {
                new_data[idx] = nullptr;
            }
        }

        if (downside)
        {
            for (size_t idx = old_chunks_amount; idx < new_capacity; ++idx)
            {
                if (data_[idx] != nullptr)
                {
                    size_t to_start = idx == old_chunks_amount ? size_ % chunk_size_ : 0;
                    for (size_t chunk_idx = to_start; chunk_idx < chunk_size_; ++chunk_idx)
                    {
                        data_[idx][chunk_idx].~T();
                    }
                }
            }
        }

        with_initial_element_ = true;
        initial_element_ = value;

        delete [] data_;

        data_     = new_data;
        capacity_ = new_capacity;
        size_     = new_size;
    }
    
    void push_back(const T& value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ * 2);
        }

        size_t needed_chunk = size_ / chunk_size_ + (size_ % chunk_size_ != 0);
        if (!data_[needed_chunk])
        {
            data_[needed_chunk] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]); 
            if (size_ % chunk_size_ != 0)
            {
                // If this chunk wasn't allocated => we must have initial element!!!!
                // Otherwise there will be trash
                assert(with_initial_element_);
                
                for (size_t idx = 0; idx < size_ % chunk_size_; ++idx)
                {
                    new(data_[needed_chunk] + size_ % chunk_size_) T(initial_element_);
                }
            }
        }

        new(data_[needed_chunk] + size_ % chunk_size_) T(value);
        size_++;
    }

    void push_back(T&& value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ * 2);
        }

        size_t needed_chunk = size_ / chunk_size_ + (size_ % chunk_size_ != 0);
        if (!data_[needed_chunk])
        {
            data_[needed_chunk] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]); 
            if (size_ % chunk_size_ != 0)
            {
                // If this chunk wasn't allocated => we must have initial element!!!!
                // Otherwise there will be trash
                assert(with_initial_element_);
                
                for (size_t idx = 0; idx < size_ % chunk_size_; ++idx)
                {
                    new(data_[needed_chunk] + size_ % chunk_size_) T(initial_element_);
                }
            }
        }

        new(data_[needed_chunk] + size_ % chunk_size_) T(std::move(value));
        size_++;
    }

    template<class... Args> 
    void emplace_back(Args&&... args)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ * 2);
        }

        size_t needed_chunk = size_ / chunk_size_ + (size_ % chunk_size_ != 0);
        if (!data_[needed_chunk])
        {
            data_[needed_chunk] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
        }

        new(data_[needed_chunk] + size_) T(std::forward<Args>(args)...);
        size_++;
    }
    
    void pop_back()
    {
        if (size_ == 0)
        {
            throw std::out_of_range("Nothing to pop\n");
        }
        
        size_t last_chunk_num = size_ / chunk_size_;
        data_[last_chunk_num][size_ % chunk_size_].~T();
        --size_;
    }

    void swap(Chunked_memory &other)
    {
        T* tmp_data = std::move(data_);
        data_ = std::move(other.data_);
        other.data_ = std::move(tmp_data);

        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_); 

        std::swap(with_initial_element_, other.with_initial_element_);
        std::swap(initial_element_, other.initial_element);
    }
};

template <size_t Chunk_size>
struct Chunked_mem
{
    template<typename T>
    using type = Chunked_memory<T, Chunk_size>;
};

#endif // CHUNCKED_MEM
