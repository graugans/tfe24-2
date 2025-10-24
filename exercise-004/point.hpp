#ifndef POINT_HPP
#define POINT_HPP

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

    private:
        double m_x;
        double m_y;


};

#endif // POINT_HPP