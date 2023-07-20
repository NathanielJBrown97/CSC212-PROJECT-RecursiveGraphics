#include "hCurve.h"
#include <cmath>


double stepOffset;
std::vector<sf::Vector2f> coordList

// Called from the main without initializing the object ,creats an object of the hCurve class
// Order is the level of recursion used to determine how many times we draw the four quadrants
// Size is the size of the window box, used to create an invisible box
void hCurve_Initialize(int order, int size, std::string fileName, sf::Color userColor) {
    hCurve hCurveObj;
    hCurveObj.setOrder(order);
    hCurveObj.setSize(size);
    int winSize = hCurveObj.getSize();
    // Sets the size of the window being
    sf::RenderWindow graphic_window(sf::VideoMode(winSize, winSize), "Hilbert's Curve");
    // Invisible box to implement the curve within, as drawing the curve without the
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

            requiredSolution.create(winSize, winSize);
            requiredSolution.update(graphic_window);
            requiredAggravation = requiredSolution.copyToImage();
            requiredAggravation.saveToFile(fileName);


            graphic_window.clear();
        }
    }
}

hCurve::hCurve(){
}

void hCurve::drawGraphic(sf::RenderWindow& graphic_window) {
    int winSize = this->getSize();
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(winSize, winSize));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color::White);
    graphic_window.draw(rectangle);

    int order = this->getOrder();
    float Size = this->getSize();
    float quadrantWidthHeight = Size / std::pow(2, order+1);
    // calculate the top left quadrant center xy coordinates
    float topLeftMidXY = ((Size / 2) * (1 - 2^(-order)));
    // the offset used based on the order of the curve, which will use the size of the window to calculate
    stepOffset = Size / std::pow(2, order+1);
}

int hCurve::drawCup(sf::Vector2f currentPos, int direction) {
    switch (direction) {
        // Upwards opening cup
        case 1:
            //implement
            break;
        // Downwards opening cup
        case 2:
            //implement
            break;
        // Leftwards opening cup
        case 3:
            //implement
            break;
       // Rightwards opening cup
        case 4:
        // implement
            break;
    }
}

// Will be used to generate the curve recursively by calling itself from the initial current coord (the bottom left quadrant) and generates from there for each order of recursion
sf::Vector2f hCurve::drawHilbertCurve(int order, int direction, sf::Vector2f currentCoord) {
    // drawCup has four cases, the direction refers to the opening segment of the shape
    if(order == 1){
        drawCup(currentCoord, direction);
    }

    else{
    // Calculate the size of the current quadrant
    int quadrant_size = 2^(order - 1)
    // notes https://www.compuphase.com/hilbert.htm
}

int hCurve::getOrder() {
    return order;
}

float hCurve::getSize() {
    return size;
}

void hCurve::setOrder(int order) {
    this->order = order;
}


void hCurve::setSize(float size) {
    this->size = size;
}
