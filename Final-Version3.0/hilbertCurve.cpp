#include <iostream>
#include "hilbertCurve.h"


int count = 1;
/////// MAIN FUNCTION TURNIED INTO INITIATE CURVE
int initiateCurve(std::string fileName) {
    const int windowWidth = 1000;
    const int windowHeight = 1000;
    // 7 is the max you can achieve before the graphics become too small to see
    const int order = 3;
    const float sideLength = 600.0f;
    const sf::Vector2f startPosition(windowWidth / 2 - sideLength / 2, windowHeight / 2 - sideLength / 2);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Hilbert Curve");
    window.setFramerateLimit(60);

    HilbertCurve hilbert(order, startPosition, sideLength);

    /// CREATION OF TEXTURE / IMAGE OBJECTS *** MUST *** OCCUR BEFORE OPENING WINDOW.
    ///Create a TEXTURE template-class object; for use in storing the graphic. Will be copied into the image object.
    sf::Texture requiredSolution;
    ///Create a IMAGE template-class object; for use in saving the texture as a PNG.
    sf::Image requiredAggravation;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        hilbert.draw(window);


        /// Start Conversion and Creation of PNG image.
        requiredSolution.create(windowWidth, windowHeight); // Create a texture of the dimensions of the graphic window
        requiredSolution.update(window); // Update the texture to be the current set of pixels within the graphic_window
        requiredAggravation = requiredSolution.copyToImage(); // Set the Image object; to be a copy of the texture, using the built in function.
        requiredAggravation.saveToFile(fileName); //Save the updated image to a file; using the filename parameter.
        /// End Creation of Image.


        window.display();
    }

    return 0;
}



////////////END ???????????



HilbertCurve::HilbertCurve(int order, sf::Vector2f start, float sideLength) {
    // Call the recursive function to generate the Hilbert curve.
    generateCurve(order, start, sideLength, 0);
}

void HilbertCurve::generateCurve(int order, sf::Vector2f start, float sideLength, int direction) {
    // Base case: If the current order is zero or less, add the starting point to the points vector and return.
    if (order <= 0) {
        points.push_back(start);
        count++;
        return;
    }

    // Calculate half of the side length for the smaller sub-curve.
    float half = sideLength / 2.0f;

    // Recursively generate the four smaller sub-curves based on the current direction.
    switch (direction) {
        case 0: /// OPENS LEFT ⏌
            // Generate the sub-curve upwards.
            generateCurve(order - 1, start, half, (direction + 1)%4);
            // Generate the sub-curve to the right.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y), half, direction);
            // Generate the sub-curve downwards.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y + half), half, direction);
            // Generate the sub-curve to the left.
            generateCurve(order - 1, sf::Vector2f(start.x , start.y + half), half, (direction + 2) % 4);
            break;
        case 1: /// OPENS UP ⏘
            // Generate the sub-curve in the downward direction.
            generateCurve(order - 1, start, half, (direction + 3) % 4);
            // Generate the sub-curve to the right.
            generateCurve(order - 1, sf::Vector2f(start.x, start.y + half), half, direction );
            // Generate the sub-curve upwards.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y + half), half, direction);
            // Generate the sub-curve to the left.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y), half, (direction + 2) % 4);
            break;
        case 2: /// OPENS DOWN
            // Generate the sub-curve upwards.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y + half), half, (direction + 1) % 4);
            // Generate the sub-curve to the left.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y), half,  direction);
            // Generate the sub-curve downwards.
            generateCurve(order - 1, start, half, direction);
            // Generate the sub-curve to the right.
            generateCurve(order - 1, sf::Vector2f(start.x, start.y + half), half, (direction + 2) % 4);
            break;
        case 3:
            /// OPENS RIGHT ⎿
            // Generate the sub-curve to the right.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y + half), half, (direction + 1) % 4);
            // Generate the sub-curve in the downward direction.
            generateCurve(order - 1, sf::Vector2f(start.x, start.y + half), half, direction);
            // Generate the sub-curve to the left.
            generateCurve(order - 1, start, half, (direction + 2) % 4);
            // Generate the sub-curve upwards.
            generateCurve(order - 1, sf::Vector2f(start.x + half, start.y ), half, direction);
            break;
        default:
            break;
    }
}

void HilbertCurve::draw(sf::RenderWindow& window) {
    // Check if there are at least two points to draw the curve.
    if (points.size() < 2)
        return;

    // Create a SFML vertex array to draw the lines.
    sf::VertexArray lines(sf::LineStrip);
    for (const auto& point : points) {
        // Add each point to the vertex array with white color.
        lines.append(sf::Vertex(point, sf::Color::White));
    }

    // Draw the Hilbert curve on the window.
    window.draw(lines);
}
