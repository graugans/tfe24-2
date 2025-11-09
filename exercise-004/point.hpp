#ifndef POINT_HPP
#define POINT_HPP



class Point
{
    private:
    int x;
    int y; 

// Getter / Setter -> set Methode sicherer als Initialisierung im Konstruktor
    public:
    Point() : x(0), y(0) {};
    void set(int xx, int yy);
    void move(int dx, int dy);
    void print() const;
};


#endif
