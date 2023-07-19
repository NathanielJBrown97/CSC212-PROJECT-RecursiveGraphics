#ifndef PROJECT2_KOCH_SNOWFLAKE_H
#define PROJECT2_KOCH_SNOWFLAKE_H
#include <SFML/Graphics.hpp>
#include <cmath>


const float ONETHIRD_GLOBAL = 0.333;
const float TWOTHIRD_GLOBAL = 0.666;


/// void function to draw a triangle used in the creation of a koch's snowflake
// passed 5 variables: const references to a top, left, and right template class of 'Vector2f' these are essentially 2d storage vectors containing 2 floats; representing an x/y respectively.
// The last two  variables will represent the template color class within SFML; which will be used to set the color of our triangle. And the RenderWindow class template to pass our window application to the function.
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

/// Function Declaration for NON-Class Specific Helper Functions...
sf::Vector2f find_center_vector(sf::Vector2f& pointA, sf::Vector2f& pointB); // Same parameter setup as above; but returns a vector2f (coordinates) of the center point.
sf::Vector2f find_top_vector(sf::Vector2f& pointA, sf::Vector2f& pointB); // Same as above; but returns the top point
sf::Vector2f normalized_vector(sf::Vector2f&); // Pass a Vector2f containing a coordinate; returns a normalized vector.



/// Class declaration of Koch's Snowflake class
class kochSnowflake
{
public:
    /// Public - Setters
    void setStageOutput(int stage); // Setter to determine the number of iterations the snowflake will undergo before drawing (i.e. 0 = Triangle | 1 = Double Triangle | 2 = Almost a Snowflake | 3 = Koch's Snowflake)
    void setInvisibleBox(float x1, float y1, float x2, float y2); //Sets the dimensions of the box to be between two coordinates. 0,0 and 1000,1000 (Scaleable; but for project leave at 0,0 -> 1000,1000 for consistent windows across algorithms.
    void setColor(const sf::Color& desiredColor); // Sets the color of the graphic to whatever color object is passed to the function.
    /// Public - Method
    void construct_snowflake(sf::RenderWindow& window); // void method function to actually start creating the snowflake. Passed our window application; establishes top, left, and right coordinates based upon our box size. If iterations is 0; no recursion. If > 0; recursive calls helper draw function.
    /// Public - Helper Function
    void recursive_koch_HELPER(sf::Vector2f pointA, sf::Vector2f pointB, int currentIteration, sf::RenderWindow& window); // void helper function for the snowflake passed 2 coord Vector2f objects, an integer to determine the current iteration, and the window object.
private:
    sf::RectangleShape invisible_box; // object of template class RectangleShape; to store an invisible set of boundaries for the construction of the koch's snowflake. (Ensures it stays within window size)
    int FinalStage; // int representing the number of iterations the Koch Snowflake will undertake. (i.e. what stage of the snowflake should be created
    sf::Color colorGraphic; // object of Color template class; will be used to determine the color of our snowflake
};

#endif //PROJECT2_KOCH_SNOWFLAKE_H
