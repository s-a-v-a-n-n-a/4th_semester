#ifndef CHUNCKED_MEM
#define CHUNCKED_MEM

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdint>
#include <cstring>

#include <stdexcept>

#include <utility>

#include <initializer_list>

#include <new>

template <typename T, size_t Chunk_size>
class Chunked_memory
{
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
      capacity_(0),
      with_initial_element_(false) 
    {}

    Chunked_memory(size_t amount, const T &initial_element)
    : data_(nullptr), 
      chunk_size_(Chunk_size), 
      size_(amount), 
      capacity_(amount / chunk_size_ + (amount % chunk_size_ != 0 )), 
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
        }

        return data_[chunk_num][index % chunk_size_];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ------------ Capacity ----------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    [[nodiscard]] size_t size()     const     { return size_; }
    [[nodiscard]] size_t max_size() const     { return SIZE_MAX * chunk_size_; }
    [[nodiscard]] size_t capacity() const     { return capacity_; }
    
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

    void resize(size_t new_size)
    {        
        size_t new_capacity = new_size / chunk_size_ + (new_size % chunk_size_ != 0);

        if (!data_)
        {
            capacity_ = new_capacity;
            return;
        }

        T** new_data = new T*[new_capacity];
        memset(new_data, 0, new_capacity);
        
        size_t old_chunks_amount = size_ / chunk_size_ + (size_ % chunk_size_ != 0);

        size_t chunks_to_copy = old_chunks_amount;
        bool downside = false;
        if (old_chunks_amount >= new_capacity)
        {
            downside = true;
            chunks_to_copy = new_capacity;
        }
        size_t elements_to_copy = std::min(new_size, size_);
            
        copy_elements(new_data, elements_to_copy);
        if (!downside)
            init_new_elements(new_data, elements_to_copy + 1, new_size - size_);

        if (downside)
        {
            free_extra_elements(new_size);
        }

        std::swap(data_, new_data);
        delete [] new_data;
        
        capacity_ = new_capacity;
    }

    void resize(size_t new_size, const T& value)
    {
        size_t new_capacity = new_size / chunk_size_ + (new_size % chunk_size_ != 0);

        if (!data_)
        {
            resize_empty_data_with_initial_to_other_initial(new_size, value);
            return;
        }

        T** new_data = new T*[new_capacity];
        memset(new_data, 0, new_capacity);
        
        size_t old_chunks_amount = size_ / chunk_size_;
        size_t chunks_to_copy = old_chunks_amount;
        bool downside = false;
        if (old_chunks_amount >= new_capacity)
        {
            downside = true;
            chunks_to_copy = new_capacity;
        }
        size_t elements_to_copy = std::min(new_size, size_);

        copy_elements(new_data, elements_to_copy);
        if (!downside)
            init_new_elements(new_data, elements_to_copy + 1, new_size - size_, value);

        if (downside)
        {
            free_extra_elements(new_size);
        }

        with_initial_element_ = true;
        initial_element_      = value;

        delete [] data_;

        data_     = new_data;
        capacity_ = new_capacity;
        size_     = new_size;
    }
    
    void push_back(const T& value)
    {
        if (size_ >= capacity_ * chunk_size_)
        {
            if (capacity_)
            {
                resize(capacity_ * chunk_size_ * 2);
            }
            else
            {
                resize(chunk_size_);
            }
        }

        if (!data_)
        {
            data_ = new T*[capacity_];
            memset(data_, 0, capacity_);
        }
        
        size_t needed_chunk = size_ / chunk_size_;
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
                    new(data_[needed_chunk] + idx) T(initial_element_);
                }
            }
        }

        new(data_[needed_chunk] + size_ % chunk_size_) T(value);
        size_++;
    }

    void push_back(T&& value)
    {
        if (size_ >= capacity_ * chunk_size_)
        {
            if (capacity_)
            {
                resize(capacity_ * chunk_size_ * 2);
            }
            else
            {
                resize(chunk_size_);
            }
        }

        if (!data_)
        {
            data_ = new T*[capacity_];
            memset(data_, 0, capacity_);
        }

        size_t needed_chunk = size_ / chunk_size_;
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
                    new(data_[needed_chunk] + idx) T(initial_element_);
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
            if (capacity_)
            {
                resize(capacity_ * 2);
            }
            else
            {
                resize(1);
            }
        }

        size_t needed_chunk = size_ / chunk_size_;
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

private:
    void copy_elements(T** copy_to, size_t copy_size)
    {
        size_t chunks_to_copy = copy_size / chunk_size_;
        for (size_t chunk_idx = 0; chunk_idx < chunks_to_copy; ++chunk_idx)
        {
            if (data_[chunk_idx] != nullptr)
            {
                copy_to[chunk_idx] = data_[chunk_idx];
            }
            else if (with_initial_element_)
            {
                copy_to[chunk_idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
                for (size_t idx = 0; idx < chunk_size_; ++idx)
                {
                    new(copy_to[chunk_idx] + idx) T(initial_element_);
                }
            }
        }

        if (copy_size % chunk_size_ != 0)
        {
            size_t last_chunk = chunks_to_copy + 1;
            for (size_t idx = 0; idx < copy_size % chunk_size_; ++idx)
            {
                new(copy_to[last_chunk] + idx) T(initial_element_);
            }
        }
    }

    void init_new_elements(T** where, size_t start_idx, size_t amount)
    {
        size_t start_chunk = start_idx / chunk_size_;
        size_t elements_to_end_initializing = amount - (chunk_size_ - start_idx + 1);
        
        size_t last_chunk = start_chunk + (elements_to_end_initializing / chunk_size_) + (elements_to_end_initializing % chunk_size_ != 0);

        for (size_t chunk_idx = start_chunk; chunk_idx < last_chunk; ++chunk_idx)
        {
            if (where[chunk_idx] == nullptr)
            {
                where[chunk_idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
            }
            
            size_t start = ((chunk_idx == start_chunk) ? start_idx % chunk_size_ : 0);
            for (size_t idx = start; idx < chunk_size_; ++idx)
            {
                if (chunk_idx * chunk_size_ + idx >= amount + start_idx)
                    break;

                new(where[chunk_idx] + idx) T(); 
            }
        }
    }

    void init_new_elements(T** where, size_t start_idx, size_t amount, const T &value)
    {
        size_t start_chunk = start_idx / chunk_size_ + (start_idx % chunk_size_ != 0);
        size_t elements_to_end_initializing = amount - start_idx;
        
        size_t last_chunk = start_chunk + (elements_to_end_initializing / chunk_size_) + (elements_to_end_initializing % chunk_size_ != 0);

        for (size_t chunk_idx = start_chunk; chunk_idx < last_chunk; ++chunk_idx)
        {
            if (where[chunk_idx] == nullptr)
            {
                where[chunk_idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
            }
            
            size_t start = ((chunk_idx == start_chunk) ? start_idx % chunk_size_ : 0);
            for (size_t idx = start; idx < chunk_size_; ++idx)
            {
                if (chunk_idx * chunk_size_ + idx >= amount + start_idx)
                    break;

                new(where[chunk_idx] + idx) T(value); 
            }
        }
    }

    void free_extra_elements(size_t start_index)
    {
        size_t start_chunk = start_index / chunk_size_;
        size_t last_chunk  = size_ / chunk_size_;
        
        for (size_t chunk_idx = start_chunk; chunk_idx < last_chunk; ++chunk_idx)
        {
            if (data_[chunk_idx] != nullptr)
            {
                size_t to_start = ((chunk_idx == start_chunk) ? (size_ % chunk_size_) : 0);
                for (size_t idx = to_start; idx < chunk_size_; ++idx)
                {
                    data_[chunk_idx][idx].~T();
                }
            }
        }
    }
    
    void resize_empty_data_with_initial_to_other_initial(size_t new_size, const T &value)
    {
        size_t new_capacity = new_size / chunk_size_ + (new_size % chunk_size_ != 0);
        
        size_t to_copy = size_;
        if (new_size < size_)
        {
            to_copy = new_size;
        }
        
        data_ = new T*[new_capacity];
        memset(data_, 0, new_capacity);
        
        size_t copyable_chunks_amount = to_copy / chunk_size_ + (to_copy % chunk_size_ != 0);
        for (size_t chunk_idx = 0; chunk_idx < copyable_chunks_amount; ++chunk_idx)
        {
            data_[chunk_idx] = (T*)(new unsigned char[chunk_size_ * sizeof(T)]);
            for (size_t idx = 0; idx < chunk_size_; ++idx)
            {
                if (chunk_idx * chunk_size_ + idx >= new_size)
                    break;
                
                if (chunk_idx * chunk_size_ + idx >= to_copy)
                {
                    new(data_[chunk_idx] + idx) T(value);
                    continue;
                }

                new(data_[chunk_idx] + idx) T(initial_element_);
            }
        }

        size_     = new_size;
        capacity_ = new_capacity;

        initial_element_      = value;
        with_initial_element_ = true;
    }
};

template <size_t Chunk_size>
struct Chunked_mem
{
    template<typename T>
    using type = Chunked_memory<T, Chunk_size>;
};

#endif // CHUNCKED_MEM
