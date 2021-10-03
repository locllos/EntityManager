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

public:

    Array(size_t capacity = 0) : size_(0)
    {
        capacity_ = capacity == 0 ? 1 : capacity;

        data_ = new elem_t[capacity];
    }

    void Append(elem_t elem)
    {
        if (size_ + 1 < capacity_)
        {
            dataRealloc(capacity_ * 2);
        }
        data_[size_++] = elem;
    }

    elem_t operator[](size_t i)
    {
        return data_[i];
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