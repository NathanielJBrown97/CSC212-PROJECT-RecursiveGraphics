#ifndef CSC212_PROJECT_2_HCURVE_H
#define CSC212_PROJECT_2_HCURVE_H

#include <vector>
#include <struct>

class hCurve{

private:

    // private member variables
    // order of the curve generation
    int order;
    // "size" of the squares
    // essentially passed into the generation function to be used to halve the size of the square in
    // each recursive call
    int initialSize;
    // dont need a whole class, but could use a struct to
    // make a pair of the x and y coordinates
    struct point{
        int x;
        int y;
    };
    std::vector<point>& points;
public:

    // def constructor
    hCurve(int order, int size, int point);
    // deconstructor
    ~hCurve();

    // getters
    getOrder();
    getSize();

    // setters
    setOrder(int order);
    setSize(int size);
    // generates and returns the curve
    generateCurve(int order, int size, int x, int y, std::vector<struct points> pointsVec);
};




#endif //CSC212_PROJECT_2_HCURVE_H
