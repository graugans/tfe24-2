#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <stdexcept>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <fmt/format.h>

namespace mystd {

template <typename T>
class myvector {
public:
    // Konstruktoren
    myvector() noexcept;
    explicit myvector(size_t count);
    
    // Destruktor
    ~myvector() noexcept;
    
    // Rule of Three
    myvector(const myvector& other);
    myvector& operator=(const myvector& other);
    
    // Öffentliche Schnittstelle
    void push_back(const T& value);
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    
    void resize(size_t new_size);
    void reserve(size_t new_cap);
    void clear() noexcept;

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
    
    // Hilfsmethode für Reallokation
    void reallocate(size_t new_capacity);
};

// ========== IMPLEMENTIERUNG ==========

// Default-Konstruktor
template <typename T>
myvector<T>::myvector() noexcept 
    : m_data(nullptr), m_size(0), m_capacity(0) {
    fmt::println("[myvector] welcome to the default CTOR!");
}

// Konstruktor mit Größe
template <typename T>
myvector<T>::myvector(size_t count)
    : m_data(nullptr), m_size(0), m_capacity(0) {
    fmt::println("[myvector] welcome to the size CTOR!");
    resize(count);
}

// Destruktor
template <typename T>
myvector<T>::~myvector() noexcept {
    fmt::println("[myvector] welcome to the DTOR!");
    delete[] m_data;
    m_data = nullptr;
}

// Copy-Konstruktor
template <typename T>
myvector<T>::myvector(const myvector& other)
    : m_data(nullptr), m_size(0), m_capacity(0) {
    fmt::println("[myvector] welcome to the copy CTOR!");
    reserve(other.m_capacity);
    m_size = other.m_size;
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
}

// Copy-Zuweisungsoperator
template <typename T>
myvector<T>& myvector<T>::operator=(const myvector& other) {
    fmt::println("[myvector] welcome to the copy assignment operator!");
    if (this != &other) {
        clear();
        reserve(other.m_capacity);
        m_size = other.m_size;
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }
    return *this;
}

// push_back
template <typename T>
void myvector<T>::push_back(const T& value) {
    if (m_size >= m_capacity) {
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reserve(new_capacity);
    }
    m_data[m_size++] = value;
}

// at() - non-const
template <typename T>
T& myvector<T>::at(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("myvector::at() - index out of range");
    }
    return m_data[index];
}

// at() - const
template <typename T>
const T& myvector<T>::at(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("myvector::at() - index out of range");
    }
    return m_data[index];
}

// operator[] - non-const
template <typename T>
T& myvector<T>::operator[](size_t index) {
    return m_data[index];
}

// operator[] - const
template <typename T>
const T& myvector<T>::operator[](size_t index) const {
    return m_data[index];
}

// size()
template <typename T>
size_t myvector<T>::size() const noexcept {
    return m_size;
}

// capacity()
template <typename T>
size_t myvector<T>::capacity() const noexcept {
    return m_capacity;
}

// resize()
template <typename T>
void myvector<T>::resize(size_t new_size) {
    if (new_size > m_capacity) {
        reserve(new_size);
    }
    
    // Neue Elemente mit T() initialisieren (Default-Wert)
    if (new_size > m_size) {
        for (size_t i = m_size; i < new_size; ++i) {
            m_data[i] = T();
        }
    }
    
    m_size = new_size;
}

// reserve()
template <typename T>
void myvector<T>::reserve(size_t new_cap) {
    if (new_cap <= m_capacity) {
        return;
    }
    reallocate(new_cap);
}

// clear()
template <typename T>
void myvector<T>::clear() noexcept {
    m_size = 0;
}

// Hilfsmethode reallocate()
template <typename T>
void myvector<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    
    // Kopiere alte Daten
    if (m_data != nullptr && m_size > 0) {
        std::copy(m_data, m_data + m_size, new_data);
        delete[] m_data;
    }
    
    m_data = new_data;
    m_capacity = new_capacity;
}

} // namespace mystd

#endif /* MY_VECTOR_HPP */