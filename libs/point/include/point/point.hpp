// Include-Guard: Beim ersten Einbinden dieser Datei ist POINT_HPP noch nicht definiert
// Dadurch wird sichergestellt, dass der Inhalt dieser Datei nur einmal eingebunden wird
#ifndef POINT_HPP
#define POINT_HPP
// Definition der Klasse Point
class Point {

    public:
        Point();
        Point(double x, double y);
        virtual ~Point();
        //virtual ~Point() = default; /* Es gibt keine speziellen Aufräumarbeiten also nutzen wir den Destrucktor der Standardbibliothek*/
        void move(double deltaX, double deltaY);
        void print() const;
        // Zusatzaufgabe
        double distance_to(const Point& other) const;
        // Getter für Tests
        const double& getX() const { return m_x; }
        const double& getY() const { return m_y; }

    private:
        double m_x;
        double m_y;
};

#endif // POINT_HPP