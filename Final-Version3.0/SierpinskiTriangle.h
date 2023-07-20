#include <SFML/Graphics.hpp>
#include <cmath>

class SierpinskiTriangle{
private:
    sf::RectangleShape invisible_box; // object of template class RectangleShape; to store an invisible set of boundaries for the construction of the koch's snowflake. (Ensures it stays within window size)
    int FinalStage; // int representing the number of iterations the Koch Snowflake will undertake. (i.e. what stage of the snowflake should be created
    sf::Color mainColor; // object of Color template class; will be used to determine main color of triangle
    sf::Color contrastColor; // used to differentiate inner triangles from parent
public:
    sf::ConvexShape drawTriangle();
    void construct_SierpinskiTriangle(sf::RenderWindow &graphic_window);
    void setInvisibleBox(float x1, float y1, float x2, float y2); //Sets the dimensions of the box to be between two coordinates. 0,0 and 1000,1000 (Scaleable; but for project leave at 0,0 -> 1000,1000 for consistent windows across algorithms.
    void recursive_sierpinski_HELPER(sf::Vector2f pointA, sf::Vector2f pointB, int currentIteration, sf::RenderWindow& window); // void helper function for the snowflake passed 2 coord Vector2f objects, an integer to determine the current iteration, and the window object.

    void setMainColor(const sf::Color& desiredColor); // Sets the color of the graphic to whatever color object is passed to the function.
    void setContrastColor(const sf::Color& color);
    void setStageOutput(int stage);
};

void constructSierpinskiTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right, const sf::Color &setColor, sf::RenderWindow &graphic_window)
{
    sf::ConvexShape shape; //creates object of ConvexShape template class within sf. Allows us to modify by adjusting points, filling, drawing, within window instance.
    shape.setPointCount(3); // Uses the built-in ConvexShape setter function to set the number of points in our shape to 3. (i.e. a triangle)
    shape.setPoint(0, top); // Uses built-in ConvexShape setter function to set point; index 0 with the coordinates stored in our passed Vector2f Top object.
    shape.setPoint(1, left); // Same as above; but with left.
    shape.setPoint(2, right); // Same as above; but with right.
    shape.setFillColor(setColor); // Uses built-in ConvexShape setter function to set the color of the triangle
    graphic_window.draw(shape); // uses the built-in RenderWindow member function to draw; the shape we just set.
}

/// Function Declaration for NON-Class Specific Helper Functions... These are template classes; can NOT be a part of SierpinskiTriangle class.
sf::Vector2f find_center_vector(sf::Vector2f& pointA, sf::Vector2f& pointB); // Same parameter setup as above; but returns a vector2f (coordinates) of the center point.
sf::Vector2f find_top_vector(sf::Vector2f& pointA, sf::Vector2f& pointB); // Same as above; but returns the top point
sf::Vector2f normalized_vector(sf::Vector2f&); // Pass a Vector2f containing a coordinate; returns a normalized vector.