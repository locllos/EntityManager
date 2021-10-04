#pragma once

#include <stdio.h>

template <typename elem_t>
class Array
{
private:

    elem_t* data_;

    size_t size_;
    size_t capacity_;

    void dataRealloc(size_t new_capacity)
    {
        elem_t* new_data = new elem_t[new_capacity];

        for (size_t i = 0; i < capacity_; ++i)
        {
            new_data[i] = data_[i];
        }
        capacity_ = new_capacity;
        
        delete[] data_;

        data_ = new_data;
    }

    bool updateCapacity(size_t new_size)
    {   
        size_t new_capacity = capacity_;
        while (new_size > new_capacity)
        {   
            new_capacity *= 2;
        }

        if (new_capacity != capacity_)
        {
            dataRealloc(new_capacity);
            return true;
        }
        return false;
    }

public:

    Array(size_t capacity = 0) : size_(0)
    {
        capacity_ = capacity == 0 ? 1 : capacity;

        data_ = new elem_t[capacity];
    }

    Array(elem_t* begin, elem_t* end)
    {   
        capacity_ = 0;
        size_ = end - begin + 1;

        dataRealloc(size_);

        elem_t* copy_data = begin;
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = copy_data[i];
        }
    }

    void singleLayerCopy(const Array& other)
    {
  		size_ = other.size_;
  		capacity_ = other.capacity_;
  		data_ = other.data_;
    }

    void Append(elem_t elem)
    {
        updateCapacity(size_ + 1);

        data_[size_++] = elem;
    }

    void Append(elem_t* begin, elem_t* end)
    {
        size_t new_size = size_ + (end - begin  + 1);
        
        updateCapacity(new_size);

        for (elem_t* current = begin; current < end; ++current)
        {
            data[size_++] = *current;
        }
    }

    void copyTo(size_t idx_start, elem_t* begin, elem_t* end)
    {   
        size_t amount = (begin - end + 1);
        size_t new_capacity = capacity_;
        
        bool was_updated = updateCapacity(idx_start + amount);

        if (was_updated)
        {
            size_ = idx_start + amount;
        }

        elem_t copy_data = begin;
        for (size_t i = idx_start; i < amount; ++i)
        {
            data_[i] = copy_data[i];
        }
    }

    void updateSize(size_t new_size)
    {
        size_ = new_size;
    }

    elem_t operator[](size_t i)
    {
        return data_[i];
    }

    void data(size_t i, elem_t elem)
    {
        data_[i] = elem;
    }
    elem_t data(size_t i)
    {
        return data_[i];
    }

    size_t size()
    {
        return size_;
    }

    ~Array()
    {
        capacity_ = 0;
        size_ = 0;

        delete[] data_;
    }
};
