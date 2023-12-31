#include "kochsnowflake.h"

/// NON-CLASS function; used within main passed setter parameters to determine creation.
// Initiates our RenderWindow creates our snowflake object, and sets the setters to respective parameters.
// Parameters X: Height and Width to determine size of our window (1000,1000 always - for consistency).
void initiateKOCH(int HEIGHT, int WIDTH) {

    //creates our object window using the template class RenderWindow. This accepts two parameters. A mode and a title.
    // The mode is an object of type VideoMode (template class of SFML library) which requires two parameters a Width and a Height. Used to scale the window's box.
    sf::RenderWindow graphic_window(sf::VideoMode(WIDTH, HEIGHT), "Koch's Snowflake");

    int stage = 4;

    kochSnowflake graphic; // creates an object of our Koch Snowflake class; calls the default constructor automatically.
    graphic.setInvisibleBox(0.0, 0.0, WIDTH, HEIGHT); // Snowflake Class setter - sets the dimensions of our invisible box in which the snowflake will be constructed; passed Width / Height from functions params.
    graphic.setColor(sf::Color::Magenta); // Snowflake Class setter - sets the color.
    graphic.setStageOutput(stage); // Snowflake Class setter - sets the number of iterations the recursive graphic generation will undergo (i.e. sets the stage of the final output drawing); passed int variable representing number of iterations.


    //While the window is open (isOpen() is a member function of sf library classes.
    while (graphic_window.isOpen()) {
        // initiate an object of SF library Event class (this will track when there is a mouse click or key press within the application
        sf::Event event;
        //while loop with the following conditional:
        // pollEvent our window; which checks if there is an event to be processed. Pass the object we created above.
        while (graphic_window.pollEvent(event)) {
            // if the current 'type' happening in our object is the Event member function closed (i.e. user clicks the X)
            // Note type is just where the user is clicking or interacting with the window.
            if (event.type == sf::Event::Closed)
                // if Event::closed is our type; call close function on our window object, which will shut the application down.
                graphic_window.close();
        }

        graphic.construct_snowflake(graphic_window); // Snowflake Class Method - calls the method used to start actually drawing our snowflake; passed the window object.
        graphic_window.display(); // calls RenderWindow function to display the graphic.
        graphic_window.clear(); // after closing the application; call the clear function to reset the window for any future graphic generations.

    }
}

/// void Method function used to construct the snowflake through the use of calling the draw helper functions
// Passed 1 parameter containing the object for our window.
void kochSnowflake::construct_snowflake(sf::RenderWindow& graphic_window)
{
    sf::Vector2f topLeft = invisible_box.getPosition(); // establishes a top left 2d vector variable to the position (using getPosition built-in getter) of our invisible box. (i.e. 0,0)
    sf::Vector2f bottomRight = sf::Vector2f(invisible_box.getSize().x, invisible_box.getSize().y); // establishes a bot right variable to the position of the size of the x and y of our invisible box.

    float oneThirdWidth = (bottomRight.x - topLeft.x)/6; // float for the width of a third of the width from bottom right x minus the top left x. (Divided by 6).
    float oneThirdHeight = (bottomRight.y - topLeft.y)/6; // same as above; but with the y values.

    // calculates the coordinates of  the LEFT point in the triangle.
    sf::Vector2f leftPoint = sf::Vector2f(topLeft.x+oneThirdWidth, bottomRight.y-2*oneThirdHeight); //2d Vector of floats; top left x value + one third of the width, and bottom right y value - 2 times the third of the height variable.
    // calculates the coordinates of  the RIGHT point in the triangle.
    sf::Vector2f rightPoint = sf::Vector2f(bottomRight.x-oneThirdWidth, bottomRight.y-2*oneThirdHeight);  // same as above; but the x value is decremented by the third of the width. NOT added. i.e. drops point on opposite side.
    // calculates the coordinates of  the TOP point in the triangle.
    sf::Vector2f top = find_top_vector(leftPoint, rightPoint); // calls the top point helper function passed the above left and right positions. Stores the return as a 2d vector float.


    /// If Stage 0; NO RECURSION.
    if(FinalStage == 0)
    {
        // Call the triangle creation; passed the three points of the triangle, the color, and the window object.
        constructTriangle(top, leftPoint, rightPoint, colorGraphic, graphic_window);
    }
        /// OTHERWISE; Stage > 0, recursion will occur in snowflake helper.
    else
    {
        /// Draw the Triangle - Recursively calls snowflake draw; current iteration will increment within.
        constructTriangle(top, leftPoint, rightPoint, colorGraphic, graphic_window); // creates our initial triangle passed top, left, right, color, and window object

    }
}

//// TODO: IMPLEMENT RECURSIVE FUNCTION TO DRAW TRIANGLES; USING KOCH'S SNOWFLAKE ALGORITHM


///////// HELPERS /////////

/// Helper - Find Center Point Vector
// Takes two 2d vector's containing coordinates, returns a 2d vector containing the point in the middle of them.
sf::Vector2f find_center_vector(sf::Vector2f& startPoint, sf::Vector2f& endPoint)
{
    // Add the two X values and the 2 Y values, divide them by 2.
    return sf::Vector2f((startPoint.x + endPoint.x)/2.0f, (startPoint.y + endPoint.y)/2.0f);
}

/// Helper - Find Top Point Vector
// Takes two 2d vectors containing coordinates for the left and right of base of the triangle.
sf::Vector2f find_top_vector(sf::Vector2f& baseLeftPoint, sf::Vector2f& baseRightPoint)
{
    /// Get height of triangle
    float side_length = std::sqrt(std::pow(baseLeftPoint.x-baseRightPoint.x, 2)*1.0f + std::pow(baseLeftPoint.y - baseRightPoint.y, 2) * 1.0f);
    float height_of_triangle = (side_length*std::sqrt(3))/2.0f; // the side length * the sqRt of 3 divided by 2 is the height

    sf::Vector2f center = find_center_vector(baseLeftPoint, baseRightPoint); // define a center point using helper passed left and right; from active functions params.
    sf::Vector2f combinedPointVector = sf::Vector2f((baseLeftPoint.x-baseRightPoint.x), (baseLeftPoint.y - baseRightPoint.y));

    combinedPointVector = normalized_vector(combinedPointVector); // normalizes the passed vector before rotating.
    combinedPointVector = sf::Vector2f(-combinedPointVector.y, combinedPointVector.x); // redefine vector to the negated y value of vector AS THE X value, and the original x value as the y value.
    return sf::Vector2f(center.x + combinedPointVector.x*height_of_triangle, center.y + combinedPointVector.y*height_of_triangle); // return a 2d vector of floats containing the center x + the combined vectors X * the height, and the same for Y.
}

/// Helper - Normalize Vector
// Takes a 2d vector of type floats - returns the normalized vector.
sf::Vector2f normalized_vector(sf::Vector2f& vector)
{
    float length = std::sqrt(std::pow(vector.x, 2.0f) + std::pow(vector.y, 2.0f)); // length = Square Root of the passed vectors X, + the square root of the passed vectors Y
    return sf::Vector2f(vector.x/length, vector.y/length); // Normalize by dividing the x and y of the passed vector by the length.
}


///////// SETTERS /////////

/// Setter - Max Iterations
// Takes an int representing what to set what stage of the snowflake we should stop at.
void kochSnowflake::setStageOutput(int stage)
{
    // set private variable to the parameters int val
    FinalStage = stage;
}

/// Setter - Invisible Box
// Takes two coordinates; which will be used to establish an invisible box in which the drawing of the snowflake graphic will occur (This prevents the image from being produced off-window)
void kochSnowflake::setInvisibleBox(float x1, float y1, float x2, float y2)
{
    invisible_box = sf::RectangleShape(); // sets invisible box to be the default constructor for RectangleShape template clas. (Needs a position and Size)
    invisible_box.setPosition(sf::Vector2f(x1, y1)); // set the position of the start of the box to equal the x1,y1 parameters from the active function.
    invisible_box.setSize(sf::Vector2f(x2 - x1, y2 - y1)); // set the size of the box (i.e. the end of the box) to x2 - x1 and y2 - y1. This will set the invisible box to be smaller than the window size. Ensuring the image is within bounds.
}

/// Setter - Color
// accepts 1 parameter of an obj distinguishing the color. From the SFML library.
void kochSnowflake::setColor(const sf::Color& desiredColor)
{
    colorGraphic = sf::Color(desiredColor); // switch the private member variable to the new color.
}
