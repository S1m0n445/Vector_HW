#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

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

    VectorBase(const VectorBase&) = delete;
    VectorBase& operator=(const VectorBase&) = delete;

    void swap(VectorBase& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
    }
};

template <typename T>
class Vector
{
private:
    VectorBase<T> base_;
    std::size_t size_;

    T* data() noexcept { return base_.data_; }
    const T* data() const noexcept { return base_.data_; }
    void destroy_elements() noexcept;

public:
    using value_type = T;

    Vector() noexcept;
    explicit Vector(std::size_t size, const T& value = T());
    Vector(std::initializer_list<T> list);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    T get(std::size_t index) const;
    void set(std::size_t index, const T& value);

    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size, T value = T());
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void clear() noexcept;
    void swap(Vector& other) noexcept;
    void print() const;

    T* begin() noexcept { return data(); }
    T* end() noexcept { return data() + size_; }
    const T* begin() const noexcept { return data(); }
    const T* end() const noexcept { return data() + size_; }
};

template <typename T>
inline void Vector<T>::destroy_elements() noexcept
{
    std::destroy(data(), data() + size_);
    size_ = 0;
}

template <typename T>
inline Vector<T>::Vector() noexcept : base_(0), size_(0) {}

template <typename T>
inline Vector<T>::Vector(std::size_t size, const T& value)
    : base_(size), size_(0)
{
    try
    {
        for (; size_ < size; ++size_)
        {
            ::new (static_cast<void*>(data() + size_)) T(value);
        }
    }
    catch (...)
    {
        destroy_elements();
        throw;
    }
}

template <typename T>
inline Vector<T>::Vector(std::initializer_list<T> list)
    : base_(list.size()), size_(0)
{
    try
    {
        for (const T& x : list)
        {
            ::new (static_cast<void*>(data() + size_)) T(x);
            ++size_;
        }
    }
    catch (...)
    {
        destroy_elements();
        throw;
    }
}

template <typename T>
inline Vector<T>::Vector(const Vector& other)
    : base_(other.size_), size_(0)
{
    try
    {
        for (; size_ < other.size_; ++size_)
        {
            ::new (static_cast<void*>(data() + size_)) T(other.data()[size_]);
        }
    }
    catch (...)
    {
        destroy_elements();
        throw;
    }
}

template <typename T>
inline Vector<T>::Vector(Vector&& other) noexcept : base_(0), size_(0)
{
    swap(other);
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other)
    {
        Vector tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        Vector tmp(std::move(other));
        swap(tmp);
    }
    return *this;
}

template <typename T>
inline Vector<T>::~Vector()
{
    destroy_elements();
}

template <typename T>
inline std::size_t Vector<T>::size() const noexcept
{
    return size_;
}

template <typename T>
inline std::size_t Vector<T>::capacity() const noexcept
{
    return base_.capacity_;
}

template <typename T>
inline bool Vector<T>::empty() const noexcept
{
    return size_ == 0;
}

template <typename T>
inline T& Vector<T>::at(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector::at: index >= size");
    }
    return data()[index];
}

template <typename T>
inline const T& Vector<T>::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector::at: index >= size");
    }
    return data()[index];
}

template <typename T>
inline T& Vector<T>::operator[](std::size_t index)
{
    return data()[index];
}

template <typename T>
inline const T& Vector<T>::operator[](std::size_t index) const
{
    return data()[index];
}

template <typename T>
inline void Vector<T>::reserve(std::size_t new_capacity)
{
    if (new_capacity <= capacity())
    {
        return;
    }

    VectorBase<T> new_base(new_capacity);
    std::size_t i = 0;
    try
    {
        for (; i < size_; ++i)
        {

            ::new (static_cast<void*>(new_base.data_ + i))
                T(std::move_if_noexcept(data()[i]));
        }
    }
    catch (...)
    {
        std::destroy(new_base.data_, new_base.data_ + i);
        throw;
    }

    std::destroy(data(), data() + size_);
    base_.swap(new_base);
}

template <typename T>
inline void Vector<T>::resize(std::size_t new_size, T value)
{
    if (new_size < size_)
    {
        std::destroy(data() + new_size, data() + size_);
        size_ = new_size;
        return;
    }

    if (new_size > capacity())
    {
        reserve(new_size);
    }

    const std::size_t old_size = size_;
    try
    {
        for (; size_ < new_size; ++size_)
        {
            ::new (static_cast<void*>(data() + size_)) T(value);
        }
    }
    catch (...)
    {
        std::destroy(data() + old_size, data() + size_);
        size_ = old_size;
        throw;
    }
}

template <typename T>
inline void Vector<T>::push_back(T&& value)
{
    if (size_ == capacity())
    {
        reserve(capacity() == 0 ? 1 : capacity() * 2);
    }
    ::new (static_cast<void*>(data() + size_)) T(std::move(value));
    ++size_;
}

template <typename T>
inline void Vector<T>::push_back(const T& value)
{

    T tmp(value);
    push_back(std::move(tmp));
}

template <typename T>
inline void Vector<T>::pop_back()
{
    if (size_ == 0)
    {
        throw std::out_of_range("Vector::pop_back: empty vector");
    }
    std::destroy_at(data() + size_ - 1);
    --size_;
}

template <typename T>
inline void Vector<T>::clear() noexcept
{
    destroy_elements();
}

template <typename T>
inline void Vector<T>::swap(Vector& other) noexcept
{
    base_.swap(other.base_);
    std::swap(size_, other.size_);
}

template <typename T>
inline T Vector<T>::get(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector::get: index >= size");
    }
    return data()[index];
}

template <typename T>
inline void Vector<T>::set(std::size_t index, const T& value)
{
    if (index >= size_)
    {
        throw std::out_of_range("Vector::set: index >= size");
    }
    data()[index] = value;
}

template <typename T>
inline void Vector<T>::print() const
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        std::cout << data()[i] << " ";
    }
    std::cout << "\n";
}