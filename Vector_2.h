#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

class Vector2
{
private:
    std::size_t size_;
    double* data_;

public:
    Vector2();
    explicit Vector2(std::size_t size, double value = 0.0);
    Vector2(std::initializer_list<double> list);
    Vector2(const Vector2& other);
    Vector2(Vector2&& other) noexcept;
    Vector2& operator=(const Vector2& other);
    Vector2& operator=(Vector2&& other) noexcept;
    ~Vector2();

    std::size_t size() const;
    double& at(std::size_t index);
    const double& at(std::size_t index) const;
    double& operator[](std::size_t index);
    const double& operator[](std::size_t index) const;
};

inline Vector2::Vector2() : size_(0), data_(nullptr) {}

inline Vector2::Vector2(std::size_t size, double value)
    : size_(size), data_(new double[size])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

inline Vector2::Vector2(std::initializer_list<double> list)
    : size_(list.size()), data_(new double[list.size()])
{
    std::size_t i = 0;
    for (double x : list)
    {
        data_[i++] = x;
    }
}

inline Vector2::Vector2(const Vector2& other)
    : size_(other.size_), data_(new double[other.size_])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

inline Vector2::Vector2(Vector2&& other) noexcept
    : size_(other.size_), data_(other.data_)
{
    other.size_ = 0;
    other.data_ = nullptr;
}

inline Vector2& Vector2::operator=(const Vector2& other)
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

inline Vector2& Vector2::operator=(Vector2&& other) noexcept
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

inline Vector2::~Vector2()
{
    delete[] data_;
}

inline std::size_t Vector2::size() const
{
    return size_;
}

inline double& Vector2::at(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector2::at: index >= size (?!)");
    }
    return data_[index];
}

inline const double& Vector2::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector2::at: index >= size (?!)");
    }
    return data_[index];
}

inline double& Vector2::operator[](std::size_t index)
{
    return data_[index];
}

inline const double& Vector2::operator[](std::size_t index) const
{
    return data_[index];
}