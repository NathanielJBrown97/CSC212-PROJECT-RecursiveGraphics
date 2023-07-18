#include <SFML/Graphics.hpp>

class SierpinskiTriangle{
private:
    int radius;
    sf::ConvexShape triangle;
public:
//    SierpinskiTriangle(sf::ConvexShape, int radius);
    sf::ConvexShape drawTriangle();
    void setRadius(int radius);
    void construct_SierpinskiTriangle(sf::RenderWindow& window);
};

void constructTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right, const sf::Color &setColor, sf::RenderWindow &graphic_window)
{
    sf::ConvexShape shape; //creates object of ConvexShape template class within sf. Allows us to modify by adjusting points, filling, drawing, within window instance.
    shape.setPointCount(3); // Uses the built-in ConvexShape setter function to set the number of points in our shape to 3. (i.e. a triangle)
    shape.setPoint(0, top); // Uses built-in ConvexShape setter function to set point; index 0 with the coordinates stored in our passed Vector2f Top object.
    shape.setPoint(1, left); // Same as above; but with left.
    shape.setPoint(2, right); // Same as above; but with right.
    shape.setFillColor(setColor); // Uses built-in ConvexShape setter function to set the color of the triangle
    graphic_window.draw(shape); // uses the built-in RenderWindow member function to draw; the shape we just set.
}