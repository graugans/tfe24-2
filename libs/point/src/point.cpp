#include "point/point.hpp"
#include <fmt/core.h> // Für fmt::print
#include <cmath>     // Für std::sqrt

template<typename T>
Point<T>::Point() {
    m_x = 0;
    m_y = 0;
    fmt::print("[lib] Konstruktor (CTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}

template<typename T>
Point<T>::Point(T x, T y) {
    m_x = x;
    m_y = y;
    fmt::print("[lib] Konstruktor (CTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}


template<typename T>
Point<T>::~Point() {
    fmt::print("[lib] Destruktor (DTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}


template<typename T>
void Point<T>::move(T deltaX, T deltaY) {
    m_x += deltaX;
    m_y += deltaY;
}


template<typename T>
void Point<T>::print() const {
    fmt::print("[lib] Point({}, {})\n", m_x, m_y);
}


template<typename T>
T Point<T>::distance_to(const Point<T>& other) const {
    const T deltaX = other.m_x - m_x;
    const T deltaY = other.m_y - m_y;
    return std::sqrt(std::pow(deltaX, 2.0) + std::pow(deltaY, 2.0));
}


// Template-Instanziierungen für die benötigten Typen
// Da wir die Klasse Point in mehreren Übersetzungseinheiten verwenden,
// müssen wir hier explizit die Instanziierungen für die gewünschten Typen angeben.
template class Point<double>;
template class Point<float>;
template class Point<int>;
