#ifndef MYSTD_MYVECTOR_HPP
#define MYSTD_MYVECTOR_HPP

#include <stdexcept>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <cstddef>

namespace mystd {

template<typename T>
class myvector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    // Hilfsfunktion: neue Kapazität berechnen (1.5x Wachstum)
    static size_t next_capacity(size_t current) noexcept {
        if (current == 0) return 1;
        return current + current / 2; // 1.5x Wachstum
    }

public:
    // Konstruktoren
    myvector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    explicit myvector(size_t count) : data_(nullptr), size_(0), capacity_(0) {
        resize(count);
    }

    // Destruktor
    ~myvector() noexcept {
        delete[] data_;
    }

    // Copy-Konstruktor
    myvector(const myvector& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.size_ > 0) {
            reserve(other.size_);
            size_ = other.size_;
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
    }

    // Copy-Zuweisungsoperator
    myvector& operator=(const myvector& other) {
        if (this != &other) {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;

            if (other.size_ > 0) {
                reserve(other.size_);
                size_ = other.size_;
                std::copy(other.data_, other.data_ + other.size_, data_);
            }
        }
        return *this;
    }

    // Push_back
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(next_capacity(capacity_));
        }
        data_[size_] = value;
        ++size_;
    }

    // at() - mit Bounds-Check
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("myvector: index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("myvector: index out of range");
        }
        return data_[index];
    }

    // operator[] - ohne Bounds-Check
    T& operator[](size_t index) noexcept {
        return data_[index];
    }

    const T& operator[](size_t index) const noexcept {
        return data_[index];
    }

    // size()
    size_t size() const noexcept {
        return size_;
    }

    // capacity()
    size_t capacity() const noexcept {
        return capacity_;
    }

    // reserve()
    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) {
            return;
        }

        T* new_data = new T[new_cap];
        if (data_) {
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_cap;
    }

    // resize()
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        if (new_size > size_) {
            // Neuen Elementen standard-initialisieren (für int: 0)
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = T();
            }
        }
        size_ = new_size;
    }

    // clear()
    void clear() noexcept {
        size_ = 0;
    }
};

} // namespace mystd

#endif // MYSTD_MYVECTOR_HPP
