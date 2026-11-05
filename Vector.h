#pragma once

#include <cstddef>
#include <stdexcept>

class Vector
{
private:
    std::size_t size_;
    double* data_;

public:
    Vector();
    Vector(std::size_t size, double value = 0.0);
    ~Vector();
    std::size_t size() const;
    double& at(std::size_t index);
    double& operator[](std::size_t index);
};

inline Vector::Vector()
    : size_(0), data_(nullptr){}

inline Vector::Vector(std::size_t size, double value)
    : size_(size), data_(new double[size])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

inline Vector::~Vector()
{
    delete[] data_;
}

inline std::size_t Vector::size() const
{
    return size_;
}

inline double& Vector::at(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index must be from 0 to (size - 1)");
    }
}

inline double& Vector::operator[](std::size_t index)
{
    return data_[index];
}