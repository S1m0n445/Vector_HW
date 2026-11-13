#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <memory>
#include <new>

template <typename T>
struct VectorBase
{
    T* data_;
    std::size_t capacity_;

    explicit VectorBase(std::size_t capacity = 0)
        : data_(capacity ? std::allocator<T>().allocate(capacity) : nullptr),
        capacity_(capacity) {}

    ~VectorBase()
    {
        if (data_)
        {
            std::allocator<T>().deallocate(data_, capacity_);
        }
    }
};

class Vector
{
private:
    std::size_t size_;
    double* data_;

public:
    Vector();
    explicit Vector(std::size_t size, double value = 0.0);
    Vector(std::initializer_list<double> list);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    std::size_t size() const;
    double& at(std::size_t index);
    const double& at(std::size_t index) const;
    double& operator[](std::size_t index);
    const double& operator[](std::size_t index) const;
};

inline Vector::Vector() : size_(0), data_(nullptr) {}

inline Vector::Vector(std::size_t size, double value)
    : size_(size), data_(new double[size])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

inline Vector::Vector(std::initializer_list<double> list)
    : size_(list.size()), data_(new double[list.size()])
{
    std::size_t i = 0;
    for (double x : list)
    {
        data_[i++] = x;
    }
}

inline Vector::Vector(const Vector& other)
    : size_(other.size_), data_(new double[other.size_])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

inline Vector::Vector(Vector&& other) noexcept
    : size_(other.size_), data_(other.data_)
{
    other.size_ = 0;
    other.data_ = nullptr;
}

inline Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    double* new_data = new double[other.size_];
    for (std::size_t i = 0; i < other.size_; ++i)
    {
        new_data[i] = other.data_[i];
    }

    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
    return *this;
}

inline Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
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
        throw std::out_of_range("Vector::at: index >= size");
    }
    return data_[index];
}

inline const double& Vector::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector::at: index >= size");
    }
    return data_[index];
}

inline double& Vector::operator[](std::size_t index)
{
    return data_[index];
}

inline const double& Vector::operator[](std::size_t index) const
{
    return data_[index];
}

