#pragma once

#include <cstddef>
#include <stdexcept>

class Vector1
{
private:
    std::size_t size_;
    double* data_;

public:
    Vector1();
    Vector1(std::size_t size, double value = 0.0);
    ~Vector1();
    std::size_t size() const;
    const double& get(std::size_t index) const;
    void set(std::size_t index, double value);
};

inline Vector1::Vector1()
    : size_(0), data_(nullptr){}

inline Vector1::Vector1(std::size_t size, double value)
    : size_(size), data_(new double[size])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

inline Vector1::~Vector1()
{
    delete[] data_;
}

inline std::size_t Vector1::size() const
{
    return size_;
}

inline const double& Vector1::get(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index must be from 0 to (size - 1)");
    }
    return data_[index];
}

inline void Vector1::set(std::size_t index, double value)
{
    if (index >= size_)
        {
            throw std::out_of_range("Index must be from 0 to (size - 1)");
        }
    data_[index] = value;
}