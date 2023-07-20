#include "SierpinskiTriangle.h"
#include "kochsnowflake.h"
#include <SFML/Graphics.hpp>

void SierpinskiTriangle::construct_SierpinskiTriangle(sf::RenderWindow& graphic_window){
    //get location of half way mark for each of three sides
    //insert triangle with points at those marks
    sf::Vector2f topLeft = invisible_box.getPosition(); // establishes a top left 2d vector variable to the position (using getPosition built-in getter) of our invisible box. (i.e. 0,0)
    sf::Vector2f bottomRight = sf::Vector2f(invisible_box.getSize().x, invisible_box.getSize().y); // establishes a bot right variable to the position of the size of the x and y of our invisible box.

    float oneHalfWidth = (bottomRight.x - topLeft.x)/4; // float for the width of a third of the width from bottom right x minus the top left x. (Divided by 6).
    float oneHalfHeight = (bottomRight.y - topLeft.y)/4; // same as above; but with the y values.

    // calculates the coordinates of  the LEFT point in the triangle.
    sf::Vector2f leftPoint = sf::Vector2f(topLeft.x+oneHalfWidth, bottomRight.y-2*oneHalfHeight); //2d Vector of floats; top left x value + one third of the width, and bottom right y value - 2 times the third of the height variable.
    // calculates the coordinates of  the RIGHT point in the triangle.
    sf::Vector2f rightPoint = sf::Vector2f(bottomRight.x-oneHalfWidth, bottomRight.y-2*oneHalfHeight);  // same as above; but the x value is decremented by the third of the width. NOT added. i.e. drops point on opposite side.
    // calculates the coordinates of  the TOP point in the triangle.
    sf::Vector2f top = find_top_vector(leftPoint, rightPoint); // calls the top point helper function passed the above left and right positions. Stores the return as a 2d vector float.
    /// If Stage 0; NO RECURSION.
    if(FinalStage == 0)
    {
        //end recursive calls
        constructTriangle(top, leftPoint, rightPoint, mainColor, graphic_window);
    }
        /// OTHERWISE; Stage > 0, recursion will occur in triangle helper.
    else
    {
        /// Draw the Triangle - Recursively calls triangle draw; current iteration will increment within.
        constructTriangle(top, leftPoint, rightPoint, mainColor, graphic_window); // creates our initial triangle passed top, left, right, color, and window object

        recursive_sierpinski_HELPER(leftPoint, rightPoint, 1, graphic_window); // draws left -> right line
        recursive_sierpinski_HELPER(top, leftPoint, 1, graphic_window); // draws top -> left line
        recursive_sierpinski_HELPER(rightPoint, top, 1, graphic_window); // draws right -> top line
    }
}

void SierpinskiTriangle::recursive_sierpinski_HELPER(sf::Vector2f startPoint, sf::Vector2f endPoint, int currentStage, sf::RenderWindow& graphic_window)
{
    /// BASE CASE
    /// If the current iteration is the max number of iterations (i.e. our desired stage)
    if(currentStage == FinalStage)
    {
        /// draw the final version of our graphic
        // define a top, left, and right vector to pass to our triangle function.
        sf::Vector2f topPoint = sf::Vector2f(0.5 * (startPoint.x - endPoint.x) + endPoint.x, 0.5 * (startPoint.y - endPoint.y) + endPoint.y);
        sf::Vector2f leftPoint = sf::Vector2f(0.5 * (startPoint.x - endPoint.x) + endPoint.x, 0.5 * (startPoint.y - endPoint.y) + endPoint.y);
        sf::Vector2f rightPoint = find_top_vector(topPoint, leftPoint); // right is set to the return from our top point calculation function.
        constructTriangle(topPoint, leftPoint, rightPoint, mainColor, graphic_window); //calls the draw for our final triangle passed these defined points
        return; // returns from the function
    }
        /// Otherwise current iteration != max iteration; a recursive call is necessary
    else
    {
        /// If recursive call scenario; triangle draw helper is being called for a side of the triangle...
        /// Establish 2 points; a point one third from the start being evaluated, the other being 1 third away from the end point of this side.
        //Define a NEXT top, left, and right vector to pass to our recursive call of the triangle draw function.
        sf::Vector2f nextTopPoint = sf::Vector2f(0.5 * (endPoint.x - startPoint.x) + startPoint.x, 0.5 * (endPoint.y - startPoint.y) + startPoint.y);
        sf::Vector2f nextLeftPoint = find_top_vector(startPoint, nextTopPoint);
        sf::Vector2f nextRightPoint = find_top_vector(nextTopPoint, endPoint);

        //draw a triangle passed the above variables in the format of top > left > right > color > graphic_window
        constructTriangle(nextTopPoint, nextLeftPoint, nextRightPoint, contrastColor, graphic_window);

        // and recursively call the same function for all the newly created sides
        /// Then... recursively call this function for EACH of the newly created sides. AND INCREMENT CURRENT ITERATION to ensure a stop point.
        recursive_sierpinski_HELPER(startPoint, nextTopPoint, currentStage+1,  graphic_window);
        recursive_sierpinski_HELPER(nextTopPoint, endPoint, currentStage+1,  graphic_window);
        recursive_sierpinski_HELPER(endPoint, nextRightPoint, currentStage+1,  graphic_window);
        recursive_sierpinski_HELPER(nextTopPoint, nextLeftPoint, currentStage+1,  graphic_window);

    }
}

void initiateSierpinski(int HEIGHT, int WIDTH, std::string fileName, sf::Color userColorMain, sf::Color userColorContrast, int endStage) {

    //creates our object window using the template class RenderWindow. This accepts two parameters. A mode and a title.
    // The mode is an object of type VideoMode (template class of SFML library) which requires two parameters a Width and a Height. Used to scale the window's box.
    sf::RenderWindow graphic_window(sf::VideoMode(WIDTH, HEIGHT), "Sierpinski's Triangle");

    int stage = endStage;

    SierpinskiTriangle graphic; // creates an object of our Sierpinski Triangle class; calls the default constructor automatically.
    graphic.setInvisibleBox(0.0, 0.0, WIDTH, HEIGHT); // Triangle Class setter - sets the dimensions of our invisible box in which the triangle will be constructed; passed Width / Height from functions params.
    graphic.setMainColor(userColorMain); // Triangle Class setter - sets the color.
    graphic.setContrastColor(userColorContrast);
    graphic.setStageOutput(stage); // Triangle Class setter - sets the number of iterations the recursive graphic generation will undergo (i.e. sets the stage of the final output drawing); passed int variable representing number of iterations.

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

        graphic.construct_SierpinskiTriangle(graphic_window);
        graphic_window.display(); // calls RenderWindow function to display the graphic.

        /// Start Conversion and Creation of PNG image.
        requiredSolution.create(WIDTH, HEIGHT); // Create a texture of the dimensions of the graphic window
        requiredSolution.update(graphic_window); // Update the texture to be the current set of pixels within the graphic_window
        requiredAggravation = requiredSolution.copyToImage(); // Set the Image object; to be a copy of the texture, using the built in function.
        requiredAggravation.saveToFile(fileName); //Save the updated image to a file; using the filename parameter.
        /// End Creation of Image.

        graphic_window.clear(); // after closing the application; call the clear function to reset the window for any future graphic generations.
    }
}

/// Setter - Invisible Box - bounds of Triangle
// Takes two coordinates; which will be used to establish an invisible box in which the drawing of the triangle
// graphic will occur (This prevents the image from being produced off-window)
void SierpinskiTriangle::setInvisibleBox(float x1, float y1, float x2, float y2)
{
    invisible_box = sf::RectangleShape(); // sets invisible box to be the default constructor for RectangleShape template class
    invisible_box.setPosition(sf::Vector2f(x1, y1)); // set the position
    invisible_box.setSize(sf::Vector2f(x2 - x1, y2 - y1)); // set the size of the box smaller than window.
}

/// Setter - Color
// accepts 1 parameter of an obj distinguishing the color. From the SFML library.
void SierpinskiTriangle::setMainColor(const sf::Color& desiredColor)
{
    mainColor = sf::Color(desiredColor); // switch the private member variable to the new color.
}

void SierpinskiTriangle::setContrastColor(const sf::Color &color) {
    contrastColor = sf::Color(color); // switch the private member variable to the new color.
}

/// Setter - Max Iterations
// Takes an int representing what to set what stage of the triangle we should stop at.
void SierpinskiTriangle::setStageOutput(int stage)
{
    // set private variable to the parameters int val
    FinalStage = stage;
}