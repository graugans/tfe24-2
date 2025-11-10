#ifndef POINT_HPP
#define POINT_HPP



class Point
{
    private:
    int px;
    int py; 

// Getter / Setter -> set Methode sicherer als Initialisierung im Konstruktor
    public:
    Point() : px(0), py(0) {};
    int x();
    int y();
    Point(int x, int y) {};
    void set(int xx, int yy);
    void move(int dx, int dy);
    void print() const;
};


#endif

