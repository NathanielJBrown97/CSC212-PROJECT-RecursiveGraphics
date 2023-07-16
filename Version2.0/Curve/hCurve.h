#ifndef CSC212_PROJECT_2_HCURVE_H
#define CSC212_PROJECT_2_HCURVE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <valarray>
#include <cmath>
////////////////////////////////////////////////////////////////////////////
class Point{
////////////////////////////////////////////////////////////////////////////
private:
    int x;
    int y;

public:
    // Default constructor // Parameters are necessary.
    Point(double x, double y);
};
////////////////////////////////////////////////////////////////////////////////////////////////
class hCurve{
/////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    private:
    ////////// Private Member Variables //////////////////////////////////
    // Order of the curve generation, represents how many times we will be recursively generating/calling the algorithm from points.
    int order;
    // The initial size of the grid, used to represent the grid size by (size x size) length x height.
    int size;
    // Starting x-value.
    double startX;
    // Starting y-value.
    double startY;
    // Vector used to hold the points of the curve prior to generating graphics.
    std::vector<Point> *points;
    ///////////////////////////////////////////////////////////////////
    public:
    ////////// Public Member Functions  //////////////////////////////////
    // Default constructor // Parameters are necessary.
    hCurve(int order, double size, double x, double y);
    // Deconstructor.
    ~hCurve();

    // Getter Functions.
    int getOrder();
    int getSize();
    int getStart(double x, double y);
    // Setter Functions.
    void setOrder(int order);
    double setSize(double size);
    void setStart(double x, double y);

    // Generates and returns the curve through a series of recursive calls into a vector of Point objects.
    void generateCurve(int order, double size, double x, double y);

    // Friend class Point
    friend class Point;
};

#endif //CSC212_PROJECT_2_HCURVE_H
