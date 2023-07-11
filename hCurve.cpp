
#include "hCurve.h"

// dont need a whole class, but could use a struct to
// make a pair of the x and y coordinates
struct point{
    int x;
    int y;
};

int hCurve::getOrder() {
    return 0;
}

int hCurve::getSize() {
    return 0;
}

int hCurve::setOrder(int order) {
    return 0;
}

int hCurve::setSize(int size) {
    return 0;
}

 hCurve::generateCurve(int order, int size, int x, int y, std::vector<struct points> pointsVec) {
 // base case: order is zero, return the current position as a single point
 // recursive algorithm, for orders greater than zero
    // four possible directions of traversal are 4 cardinal directions NESW
    // call the first direction, then recursively call the 4 other directions within it
        // calls update the position with an offset, offsets determined by the size of the current square and the direction


    return struct<points> point;
}

int hCurve::getOrder() {
    return 0;
}
