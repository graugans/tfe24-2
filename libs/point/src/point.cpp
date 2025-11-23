#include "point/point.hpp"
#include <fmt/core.h> // Für fmt::print
#include <cmath>     // Für std::sqrt

Point::Point(): m_x(0.0), m_y(0.0) {
    // Die Werte für m_x und m_y werden in der Initialisierungsliste gesetzt
    fmt::print("[lib] Standardkonstruktor (CTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}

Point::Point(double x, double y) {
    m_x = x;
    m_y = y;
    fmt::print("[lib] Konstruktor (CTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}

Point::~Point() {
    fmt::print("[lib] Destruktor (DTOR) aufgerufen: Point({}, {})\n", m_x, m_y);
}

void Point::move(double deltaX, double deltaY) {
    m_x += deltaX;
    m_y += deltaY;
}


void Point::print() const {
    fmt::print("[lib] Point({}, {})\n", m_x, m_y);
}


double Point::distance_to(const Point& other) const {
    const double deltaX = other.m_x - m_x;
    const double deltaY = other.m_y - m_y;
    return std::sqrt(std::pow(deltaX, 2.0) + std::pow(deltaY, 2.0));
}