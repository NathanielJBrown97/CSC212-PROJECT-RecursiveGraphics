#ifndef CSC212_PROJECT_2_HCURVE_H
#define CSC212_PROJECT_2_HCURVE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Point{
private:
    int x;
    int y;

public:
    // Default constructor // Parameters are necessary.
    Point(int x, int y);
};


class hCurve{
    private:
    ////////// private member variables //////////////////////////////////

    // Order of the curve generation, represents how many times we will be recursively generating/calling the algorithm from points.
    int order;
    // The initial size of the grid, used to represent the grid size by (size x size) length x height.
    int size;
    // Starting x-value.
    int startX;
    // Starting y-value.
    int startY;

    // Vector used to hold the points of the curve prior to generating graphics.
    std::vector<Point> *points;

    public:
    // Default constructor // Parameters are necessary.
    hCurve(int order, int size, int x, int y);
    // Deconstructor.
    ~hCurve();

    // Getter Functions.
    getOrder();
    getSize();

    // Setter Functions.
    setOrder(int order);
    setSize(int size);
    // generates and returns the curve
    Point generateCurve(int order, int size, int x, int y);

    friend class Point;
};





#endif //CSC212_PROJECT_2_HCURVE_H
