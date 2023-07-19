#include "hCurve.h"


// Called from the main without initializing the object ,creats an object of the hCurve class
// Order is the level of recursion used to determine how many times we draw the four quadrants
// Size is the size of the window box, used to create an invisible box
void hCurve_Initialize(int order, int size, int x, int y) {
    hCurve hCurveObj;
    hCurveObj.setOrder(order);
    hCurveObj.setSize(size);
    int winSize = hCurveObj.getSize();
    // Sets the size of the window being
    sf::RenderWindow graphic_window(sf::VideoMode((winSize - 2), (winSize- 1), "Hilbert's Curve");
    // Invisible box to implement the curve within, as drawing the curve without the
    graphic.set(0.0, 0.0, winSize, winSize);
    graphic_window.setFramerateLimit(60);

    // Creation of Texture / Image Objects, which must occur before the window is opened
    ///Create a TEXTURE template-class object; for use in storing the graphic. Will be copied into the image object.
    sf::Texture requiredSolution;
    ///Create a IMAGE template-class object; for use in saving the texture as a PNG.
    sf::Image requiredAggravation;

    while(graphic_window.isOpen()) {
        sf::Event event;
        while(graphic_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                graphic_window.close();
            }
            hCurveObj.drawGraphic(graphic_window);
            graphic_window.display();

            requiredSolution.create()
            requiredSolution.update(graphic_window)
        }
    }
}

hCurve::hCurve(){
}

void hCurve::drawGraphic(sf::RenderWindow& graphic_window) {

}

// Will be used to generate the curve recursively by calling itself from the initial current coord (the bottom left quadrant) and generates from there for each order of recursion
 sf::Vector2f hCurve::generateCurve(int order, float size,sf::Vector2f currentCoord, int travrseDir){
    // Initialize vector of coordinates to be returned.
    std::vector<sf::Vector2f> coordinatesVector;
    // Generate initial/recursive point(s) to iterated over.
    // Base Case: Order is zero, return the current position as a single point to the coordinatesVector.
    if (order == 0) {
    return currentCoord; // Since we return this at the end of recursive call stack, we steadily chain all of the calls' current coords back onto this vector
    }
    // Implicitly defined by the order of recursion, offset must be divided further by the amount of times the algorithm is called to allow for a scaled offset based off of the order of curve complexity
    // and using the x
    float xCurrent = currentCoord.x;
    float yCurrent = currentCoord.y;
    float scaledOffset = size / 2.0; // As said above, offset divided by 2 for each call to generate smaller point offsets.
    // recursive algorithm, for orders greater than zero

        // Four possible ways to draw the curve, starting from the base case where it is drawn
        // from the bottom left quadrant, and going counter-clockwise, until the four quadrants are visited, and appending coordinates.
        if(travrseDir == 0) {
            // Bottom-left quadrant
            sf::Vector2f quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent), 3);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent + scaledOffset), 0);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent + scaledOffset), 1);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent), 2);
            coordinatesVector.push_back(quadCoordinates);
        }
        else if (travrseDir == 1) {
            // Bottom-right quadrant
            sf::Vector2f quadCoordinates = generateCurve((order - 1), scaledOffset,  sf::Vector2f(xCurrent + scaledOffset, yCurrent), 2);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent + scaledOffset), 1);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent + scaledOffset), 0);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent), 3);
            coordinatesVector.push_back(quadCoordinates);
        }
        else if (travrseDir == 2) {
            // Top-right quadrant
            sf::Vector2f quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent + scaledOffset), 1);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent + scaledOffset), 0);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent), 3);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent), 2);
            coordinatesVector.push_back(quadCoordinates);
        }
        else if (travrseDir == 3) {
            // Top-left quadrant
            sf::Vector2f  quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent + scaledOffset, yCurrent + scaledOffset), 0);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent + scaledOffset), 1);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset, sf::Vector2f(xCurrent, yCurrent), 2);
            coordinatesVector.push_back(quadCoordinates);
            quadCoordinates = generateCurve((order - 1), scaledOffset,sf::Vector2f(xCurrent + scaledOffset, yCurrent), 3);
            coordinatesVector.push_back(quadCoordinates);
        }

        // the end of this call wont actually return anything of value
        // what we're using is the member variable that we're storing the coordinatesVector into, and call that at the end of our generation
        // it's a bit crude but it works
    this->coordinates = coordinatesVector;
return sf::Vector2f(0,0);
}

int hCurve::getOrder() {
    return order;
}

float hCurve::getSize() {
    return size;
}

void hCurve::setOrder(int order) {
    return 0;
}


void hCurve::setSize(int size) {
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
