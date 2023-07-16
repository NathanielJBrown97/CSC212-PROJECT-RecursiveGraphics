#include "hCurve.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

hCurve::hCurve(int order, int size, int x, int y) {
    this->order = order;
    this->size = size;
    this->startX = x;
    this->startY = y;

}




// Will be used to generate the curve recursively by calling itself from a starting point, and then
Point hCurve::generateCurve(int order, int size, int x, int y) {
    // Generate initial/recursive point(s) to iterated over.
    // Base Case: Order is zero, return the current position as a single point.
    if (order == 0) {

    }
        // recursive algorithm, for orders greater than zero
        // four possible directions of traversal are 4 cardinal directions NESW
        // call the first direction, then recursively call the 4 other directions within it
        // calls update the position with an offset, offsets determined by the size of the current square and the direction
        // repeat with the next 3 directions till the order is 0
    else {
        // Northern direction call.
        // rough approximation of the function?
        // newPoint = generateCurve(order - 1, size, x + size, y);

    }
}

int hCurve::getOrder() {
    return order;
}

int hCurve::getSize() {
    return size;
}

int hCurve::setOrder(int order) {
    return 0;
}


int hCurve::setSize(int size) {
    return 0;
}

hCurve::~hCurve() {
    // TODO: Deconstructor implementation

}

    // TODO: Implement the SFML functions
        // - Convert the vector to an SFML vector
        // - Implement the window drawing function
        // - Import the color manipulation function from repo (possibly turn the code into a callable function across the program
        // - TBD

