#include "kochsnowflake.h"

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
///////                 SUMMARY OF FILE                       ///////////
////   1.) initiateKoch function will be called via main; which      ////
////   will create an object of KochSnowflake class called graphic.  ////
////   basic setters will be applied to establish, color, stage      ////
////   of snowflake and dimensions of the box the graphic will be    ////
////   created within. Opens a graphic window; and calls the         ////
////   construction of snowflake.                                    ////
////   2.) Construction method will establish a top, left and right  ////
////   vector coordinates based on the box it can work within. This  ////
////   method will then call the helper to recursively draw the koch ////
////   snowflake.                                                    ////
////   3.) This function recursively draws the snowflake by passing  ////
////   the stage int; which represents the end iteration. If there   ////
////   are additional iterations left to be processed; the program   ////
////   will draw a triangle  with passed points and call itself      ////
////   to then draw sub-triangles within each triangle               ////
////   4.) a variety of helpers are used throughout this process;    ////
////   defined at the bottom they allow for easy finding of center   ////
////   and top points to pass into the recursive calls               ////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




/// NON-CLASS function; used within main passed setter parameters to determine creation.
// Initiates our RenderWindow creates our snowflake object, and sets the setters to respective parameters.
// Parameters X: height and Width to determine size of our window (1000,1000 always - for consistency).
void initiateKOCH(int height, int width, std::string fileName, sf::Color userColor, int stage) {

    //creates our object window using the template class RenderWindow. This accepts two parameters. A mode and a title.
    // The mode is an object of type VideoMode (template class of SFML library) which requires two parameters a Width and a height. Used to scale the window's box.
    sf::RenderWindow graphic_window(sf::VideoMode(width, height), "Koch's Snowflake");

    kochSnowflake graphic; // creates an object of our Koch Snowflake class; calls the default constructor automatically.
    graphic.setInvisibleBox(0.0, 0.0, width, height); // Snowflake Class setter - sets the dimensions of our invisible box in which the snowflake will be constructed; passed Width / height from functions params.
    graphic.setColor(userColor); // Snowflake Class setter - sets the color.
    graphic.setStageOutput(stage); // Snowflake Class setter - sets the number of iterations the recursive graphic generation will undergo (i.e. sets the stage of the final output drawing); passed int variable representing number of iterations.


    /// CREATION OF TEXTURE / IMAGE OBJECTS *** MUST *** OCCUR BEFORE OPENING WINDOW.
    ///Create a TEXTURE template-class object; for use in storing the graphic. Will be copied into the image object.
    sf::Texture requiredSolution;
    ///Create a IMAGE template-class object; for use in saving the texture as a PNG.
    sf::Image requiredAggravation;

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

        /// Start Conversion and Creation of PNG image.
        requiredSolution.create(width, height); // Create a texture of the dimensions of the graphic window
        requiredSolution.update(graphic_window); // Update the texture to be the current set of pixels within the graphic_window
        requiredAggravation = requiredSolution.copyToImage(); // Set the Image object; to be a copy of the texture, using the built in function.
        requiredAggravation.saveToFile(fileName); //Save the updated image to a file; using the filename parameter.
        /// End Creation of Image.

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
    float oneThirdheight = (bottomRight.y - topLeft.y)/6; // same as above; but with the y values.

    // calculates the coordinates of  the LEFT point in the triangle.
    sf::Vector2f leftPoint = sf::Vector2f(topLeft.x+oneThirdWidth, bottomRight.y-2*oneThirdheight); //2d Vector of floats; top left x value + one third of the width, and bottom right y value - 2 times the third of the height variable.
    // calculates the coordinates of  the RIGHT point in the triangle.
    sf::Vector2f rightPoint = sf::Vector2f(bottomRight.x-oneThirdWidth, bottomRight.y-2*oneThirdheight);  // same as above; but the x value is decremented by the third of the width. NOT added. i.e. drops point on opposite side.
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
        recursive_koch_HELPER(leftPoint, rightPoint, 1, graphic_window); // draws left -> right line
        recursive_koch_HELPER(top, leftPoint, 1, graphic_window); // draws top -> left line
        recursive_koch_HELPER(rightPoint, top, 1, graphic_window); // draws right -> top line

    }
}

/// Recursive Helper - progresses stages of iteration; creating the koch's snowflake
// Passed 5 Parameters: Start and end position 2d vectors, an int for our current iteration, and our window object.
void kochSnowflake::recursive_koch_HELPER(sf::Vector2f startPoint, sf::Vector2f endPoint, int currentStage, sf::RenderWindow& graphic_window)
{
    /// BASE CASE
    /// If the current iteration is the max number of iterations (i.e. our desired stage)
    if(currentStage == FinalStage)
    {
        /// draw the final version of our graphic
        // define a top, left, and right vector to pass to our triangle function.
        sf::Vector2f topPoint = sf::Vector2f(0.33 * (startPoint.x - endPoint.x) + endPoint.x, 0.33 * (startPoint.y - endPoint.y) + endPoint.y); // top = 2d vector storing (x,y) || X = One third the difference of start pos x - end pos x, + end pos x. Y = the same as previous; substitute y for x.
        sf::Vector2f leftPoint = sf::Vector2f(0.66 * (startPoint.x - endPoint.x) + endPoint.x, 0.66 * (startPoint.y - endPoint.y) + endPoint.y); // left = same as above, but with two thirds substituted for one third.
        sf::Vector2f rightPoint = find_top_vector(topPoint, leftPoint); // right is set to the return from our top point calculation function.
        constructTriangle(topPoint, leftPoint, rightPoint, colorGraphic, graphic_window); //calls the draw for our final triangle passed these defined points
        return; // returns from the function
    }
        /// Otherwise current iteration != max iteration; a recursive call is necessary
    else
    {
        /// If recursive call scenario; snowflake draw helper is being called for a side of the triangle...
        /// Establish 2 points; a point one third from the start being evaluated, the other being 1 third away from the end point of this side.
        //Define a NEXT top, left, and right vector to pass to our recursive call of the snowflake draw function.
        sf::Vector2f nextThirdPoint = sf::Vector2f(0.33 * (endPoint.x - startPoint.x) + startPoint.x, 0.33 * (endPoint.y - startPoint.y) + startPoint.y); // nextThird = 2d vector storing (x,y) || X = One third the difference of start pos x - end pos x, + end pos x. Y = the same as previous; substitute y for x.
        sf::Vector2f nextTwoThirdPoint = sf::Vector2f(0.66 * (endPoint.x - startPoint.x) + startPoint.x, 0.66 * (endPoint.y - startPoint.y) + startPoint.y); // nextTwoThird =  same as above, but with two thirds substituted for one third.
        sf::Vector2f nextTopPoint = find_top_vector(nextTwoThirdPoint, nextThirdPoint); // pass the nextThird and nextTwoThird points to our top point function to return a new top point of the two points.


        //draw a triangle passed the above variables in the format of top > left > right > color > graphic_window
        constructTriangle(nextThirdPoint, nextTwoThirdPoint, nextTopPoint, colorGraphic, graphic_window);

        // and recursively call the same function for all the newly created sides
        /// Then... recursively call this function for EACH of the newly created sides. AND INCREMENT CURRENT ITERATION to ensure a stop point.
        recursive_koch_HELPER(startPoint, nextThirdPoint, currentStage+1,  graphic_window); //passed active functions startCoords, nextThird value as our end, incremented iteration, and our window.
        recursive_koch_HELPER(nextTwoThirdPoint, endPoint, currentStage+1,  graphic_window); //passed twoThirds, active functions endCoords, incremented iteration, and our window.
        recursive_koch_HELPER(nextThirdPoint, nextTopPoint, currentStage+1,  graphic_window); //passed nextThird vlaue, nextTop value, incremented iteration, and our window.
        recursive_koch_HELPER(nextTopPoint, nextTwoThirdPoint, currentStage+1,  graphic_window); //passed nextTop value, twoThirds value, incremented iteration, and our window.
    }
}

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

/// Setter - Invisible Box - bounds of Snowflake
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
