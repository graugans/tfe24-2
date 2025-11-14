#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace mystd {

template<typename T>
class myvector {
public:
    // Konstruktoren & Destruktor
    myvector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}
    
    explicit myvector(size_t count) : m_size(count), m_capacity(count) {
        if (count > 0) {
            m_data = new T[count];
            // default-initialize alle Elemente
            for (size_t i = 0; i < count; ++i) {
                m_data[i] = T();
            }
        } else {
            m_data = nullptr;
        }
    }
    
    ~myvector() noexcept {
        delete[] m_data;
    }
    
    // Rule of Three: Copy-Konstruktor
    myvector(const myvector& other) 
        : m_size(other.m_size), m_capacity(other.m_capacity) {
        if (m_capacity > 0) {
            m_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_data[i] = other.m_data[i];
            }
        } else {
            m_data = nullptr;
        }
    }
    
    // Rule of Three: Copy-Zuweisungsoperator
    myvector& operator=(const myvector& other) {
        if (this != &other) {
            // Alte Daten löschen
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            
            // Neue Daten allozieren und kopieren
            if (m_capacity > 0) {
                m_data = new T[m_capacity];
                for (size_t i = 0; i < m_size; ++i) {
                    m_data[i] = other.m_data[i];
                }
            } else {
                m_data = nullptr;
            }
        }
        return *this;
    }
    
    // Modifizierer
    void push_back(const T& value) {
        if (m_size == m_capacity) {
            // Kapazität verdoppeln oder auf 1 setzen
            size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
            reserve(new_cap);
        }
        m_data[m_size++] = value;
    }
    
    void resize(size_t new_size) {
        if (new_size > m_capacity) {
            reserve(new_size);
        }
        
        // Neue Elemente default-initialize
        if (new_size > m_size) {
            for (size_t i = m_size; i < new_size; ++i) {
                m_data[i] = T();
            }
        }
        // (Alte Elemente bleiben, wenn new_size < m_size)
        
        m_size = new_size;
    }
    
    void reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;  // nichts zu tun
        }
        
        // Neuen Buffer allozieren
        T* new_data = new T[new_capacity];
        
        // Alte Elemente kopieren
        for (size_t i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }
        
        // Alten Buffer freigeben
        delete[] m_data;
        
        m_data = new_data;
        m_capacity = new_capacity;
    }
    
    void clear() noexcept {
        m_size = 0;
        // m_data bleibt alloziert, m_capacity unverändert
    }
    
    // Accessoren
    T& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("myvector::at() index out of range");
        }
        return m_data[index];
    }
    
    const T& at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("myvector::at() index out of range");
        }
        return m_data[index];
    }
    
    T& operator[](size_t index) noexcept {
        return m_data[index];
    }
    
    const T& operator[](size_t index) const noexcept {
        return m_data[index];
    }
    
    // Größen-Abfragen
    size_t size() const noexcept {
        return m_size;
    }
    
    size_t capacity() const noexcept {
        return m_capacity;
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

}  // namespace mystd

#endif /* MYVECTOR_HPP */