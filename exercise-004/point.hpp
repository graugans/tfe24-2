#ifndef POINT_HPP
#define POINT_HPP

class Point
{
    private:
    int px;
    int py;

    public:
    Point() { set(0, 0); };
    Point(int x, int y) { set(x, y); };

    // Methoden: Getter
    int x() const { return px; };
    int y() const { return py; };

    // Methoden: Setter
    void set(int x, int y) { px = x; py = y; };

    // Methoden: Manipulator
    void move(int dx, int dy) { set(x()+dx, y()+dy); };

    void print() const;
};

#endif
