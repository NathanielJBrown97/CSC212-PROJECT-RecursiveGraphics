#include "hCurve.h"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

//////////////////////////////// Public Methods //////////////////////////////////
hCurve::hCurve(int order, double size, double x, double y) {
    setOrder(order);
    setSize(size);
    setStart(x, y);
    generateCurve(this->order, this->size, this->startX, this->startY);
}


// Will be used to generate the curve recursively by calling itself from a starting point, and then
void hCurve::generateCurve(int order, double size, double x, double y) {
    // Generate initial/recursive point(s) to iterated over.
    // Base Case: Order is zero, return the current position as a single point.
    if (order == 0) {
        // essentially start from the current position
        this->points->push_back(Point{x,y});
    }
    // Recursive algorithm, for orders greater than zero, start with the starting point and call itself from the four quadrants of the grid.
    else {
        // Size will be used to determine the size of the grid, and thus, the offset that we use to create each new point.
        // Essentially, dictates the length of the line from each point as a result of being the size of the grid.
        // The offset will be divided by 2^order to downscale the offset based on the current order of each call to provide a curve that is variably based on the size of the grid.
        double offset = size / pow(2, order);
        // four possible directions of traversal are 4 cardinal directions NE, NW, SE, SW.
        // call the first direction, then recursively call the 4 other directions within it
        // SE Quadrant call.
        generateCurve(order - 1, size, x + offset, y);
        // NW Quadrant call.
        generateCurve(order - 1, size, x, y - offset);
        // NE Quadrant call.
        generateCurve(order - 1, size, x, y + offset);
        // SW Quadrant call.
        generateCurve(order - 1, size, x - offset, y);
        // Points vector will eventually contain points starting from the SW quadrant and ending at the SE quadrant.
    }
}

int hCurve::getOrder() {
    return order;
}

int hCurve::getSize() {
    return size;
}
int hCurve::getStart(double x, double y){
    return startX;
}

void hCurve::setOrder(int order) {
    this->order = order;
}


double hCurve::setSize(double size) {
    this->size = size;
}

void hCurve::setStart(double x, double y) {
    this->startX = x;
    this->startY = y;
}

hCurve::~hCurve() {
    // TODO: Deconstructor implementation

}

// TODO: Implement the SFML functions
        // - Convert the vector to an SFML vector
        // - Implement the window drawing function
        // - Import the color manipulation function from repo (possibly turn the code into a callable function across the program