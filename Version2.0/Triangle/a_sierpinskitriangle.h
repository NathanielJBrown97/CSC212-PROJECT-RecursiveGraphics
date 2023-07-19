#ifndef INC_212_PROJECT2_SIERPINSKITRIANGLE_H
#define INC_212_PROJECT2_SIERPINSKITRIANGLE_H
#include <SFML/Graphics.hpp>
#include <cmath>

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


class sierpinskiTriangle {
    private:
        int radius;
        sf::ConvexShape triangle;
    public:
        void setStageOutput(int stage); // Setter to determine the number of iterations the snowflake will undergo before drawing (i.e. 0 = Triangle | 1 = Double Triangle | 2 = Almost a Snowflake | 3 = Koch's Snowflake)
        void setInvisibleBox(float x1, float y1, float x2, float y2); //Sets the dimensions of the box to be between two coordinates. 0,0 and 1000,1000 (Scaleable; but for project leave at 0,0 -> 1000,1000 for consistent windows across algorithms.
        void setColor(const sf::Color& desiredColor); // Sets the color of the graphic to whatever color object is passed to the function.

};


#endif //INC_212_PROJECT2_SIERPINSKITRIANGLE_H
