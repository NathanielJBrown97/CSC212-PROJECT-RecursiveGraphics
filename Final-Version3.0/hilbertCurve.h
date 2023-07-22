#ifndef HELLOSFML_HCURVE_H
#define HELLOSFML_HCURVE_H

#include <SFML/Graphics.hpp>
#include <vector>

class HilbertCurve {
private:
    // Vector to store the points of the Hilbert curve.
    std::vector<sf::Vector2f> points;

    // Recursive function to generate the Hilbert curve.
    // It takes the current order, starting position, side length, and direction as arguments.
    //order = hCurve Stage
    void generateCurve(int order, sf::Vector2f start, float sideLength, int direction);

public:
    // Constructor
    // initialize curve with given order, starting position and side length
    HilbertCurve(int order, sf::Vector2f start, float sideLength);

    // draw curve in SFML window.
    void draw(sf::RenderWindow& window);

};


#endif //HELLOSFML_HCURVE_H
