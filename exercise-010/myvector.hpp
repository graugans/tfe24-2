#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace tfe24 {

template <typename T>
class myvector {
public:
    // default ctor
    myvector() noexcept : data_(nullptr), size_(0), cap_(0) {}

    // explicit ctor with count
    explicit myvector(std::size_t count) : data_(nullptr), size_(0), cap_(0) {
        if (count > 0) {
            data_ = new T[count];
            // value-initialize new elements
            for (std::size_t i = 0; i < count; ++i) data_[i] = T{};
            size_ = count;
            cap_ = count;
        }
    }

    // copy constructor
    myvector(const myvector& other) : data_(nullptr), size_(0), cap_(0) {
        if (other.size_ > 0) {
            data_ = new T[other.cap_];
            for (std::size_t i = 0; i < other.size_; ++i) data_[i] = other.data_[i];
            size_ = other.size_;
            cap_ = other.cap_;
        }
    }

    // copy assignment (copy-and-swap)
    auto operator=(myvector other) -> myvector& {
        swap(other);
        return *this;
    }

    // destructor
    ~myvector() {
        delete[] data_;
    }

    // push_back
    void push_back(const T& value) {
        if (size_ >= cap_) {
            std::size_t newcap = (cap_ == 0) ? 1 : cap_ * 2;
            reserve(newcap);
        }
        data_[size_++] = value;
    }

    // at with bounds checking
    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("myvector::at: index out of range");
        return data_[index];
    }
    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("myvector::at: index out of range");
        return data_[index];
    }

    // operator[] without bounds checking
    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    // size
    std::size_t size() const noexcept { return size_; }

    // capacity
    std::size_t capacity() const noexcept { return cap_; }

    // reserve
    void reserve(std::size_t new_cap) {
        if (new_cap <= cap_) return;
        T* newdata = new T[new_cap];
        // move/copy existing elements
        for (std::size_t i = 0; i < size_; ++i) newdata[i] = data_[i];
        delete[] data_;
        data_ = newdata;
        cap_ = new_cap;
    }

    // resize
    void resize(std::size_t new_size) {
        if (new_size > cap_) reserve(new_size);
        // value-initialize new elements if expanding
        for (std::size_t i = size_; i < new_size; ++i) data_[i] = T{};
        size_ = new_size;
    }

    // clear (keeps capacity)
    void clear() noexcept { size_ = 0; }

    // swap
    void swap(myvector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t cap_;
};

} // namespace tfe24

#endif // MYVECTOR_HPP