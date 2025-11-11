#include <fmt/core.h>

// Include-Guard: Beim ersten Einbinden dieser Datei ist POINT_HPP noch nicht definiert
// Dadurch wird sichergestellt, dass der Inhalt dieser Datei nur einmal eingebunden wird
#ifndef POINT_HPP
#define POINT_HPP
// Definition der Klasse Point

template <typename T>
class Point {

    public:
        Point();
        Point(T x, T y);
        virtual ~Point();
        //virtual ~Point() = default; /* Es gibt keine speziellen Aufräumarbeiten also nutzen wir den Destrucktor der Standardbibliothek*/
        void move(T deltaX, T deltaY);
        void print() const;
        // Zusatzaufgabe
        T distance_to(const Point<T>& other) const;
        // Getter für Tests
        const T& getX() const { return m_x; }
        const T& getY() const { return m_y; }

        // Operatoren
        bool operator==(const Point<T>& rhs) const { return m_x == rhs.m_x && m_y == rhs.m_y; }
        bool operator!=(const Point<T>& rhs) const { return !(*this == rhs); }
        // Skalierungsoperator
        Point<T>& operator*(T factor)  { 
            m_x *= factor;
            m_y *= factor;
            return *this; 
        }

        // Zuweisungsoperator
        Point<T> operator=(const Point<T>& rhs) { 
            m_x = rhs.m_x;
            m_y = rhs.m_y;
            return *this; 
        }

        // Let's make Friends
        // fmt-Integration
        friend struct fmt::formatter<Point<T>>;

    private:
        T m_x;
        T m_y;
};


namespace fmt {
template <typename T>
struct formatter<Point<T>> : formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    // Fuer den Zugriff auf die privaten Mitglieder m_x und m_y
    // nutzen wir die Freundschaftsdeklaration in der Point-Klasse
    // friend struct fmt::formatter<Point<T>>;
    return format_to(ctx.out(), "Point<T>({}, {})",p.m_x, p.m_y);
  }
};

}

#endif // POINT_HPP