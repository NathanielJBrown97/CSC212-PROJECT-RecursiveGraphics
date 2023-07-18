#include "SierpinskiTriangle.h"
#include <SFML/Graphics.hpp>
/*

SierpinskiTriangle::SierpinskiTriangle(sf::ConvexShape triangle, int radius){
    this->triangle = triangle;
    this->radius = radius;
}

sf::ConvexShape SierpinskiTriangle::drawTriangle() {
    this->triangle.setFillColor(sf::Color::Cyan);
    if (this->radius < 10){
        //set condition to end recursive call
    }else {
        //create smaller triangles, alternate color
        //decrement radius

        //change triangle color to white
        this->triangle.setFillColor(sf::Color::Magenta);
        this->triangle.setPosition(radius, radius);
        this->radius /= 2;
        drawTriangle();
        //change new triangles to red
    }

    return this->triangle;
}*/

void SierpinskiTriangle::setRadius(int radius) {
    this->radius = radius;
}

void SierpinskiTriangle::construct_SierpinskiTriangle(sf::RenderWindow& graphic_window){
    //calculate coordinates - do i need invisible box?
    //get location of half way mark for each of three sides
    //insert triangle with points at those marks


    float oneHalfWidth = (left - topLeft.x)/2; // float for the width of a third of the width from bottom right x minus the top left x. (Divided by 6).
    float oneHalfHeight = (bottomRight.y - topLeft.y)/2; // same as above; but with the y values.

    // calculates the coordinates of  the LEFT point in the triangle.
    sf::Vector2f leftPoint = sf::Vector2f(topLeft.x+oneHalfWidth, bottomRight.y-2*oneHalfHeight); //2d Vector of floats; top left x value + one third of the width, and bottom right y value - 2 times the third of the height variable.
    // calculates the coordinates of  the RIGHT point in the triangle.
    sf::Vector2f rightPoint = sf::Vector2f(bottomRight.x-oneHalfWidth, bottomRight.y-2*oneHalfHeight);  // same as above; but the x value is decremented by the third of the width. NOT added. i.e. drops point on opposite side.
    // calculates the coordinates of  the TOP point in the triangle.
    sf::Vector2f top = find_top_vector(leftPoint, rightPoint); // calls the top point helper function passed the above left and right positions. Stores the return as a 2d vector float.
    /// If Stage 0; NO RECURSION.
    if(radius == 0)
    {
        //end recursive calls
    }
        /// OTHERWISE; Stage > 0, recursion will occur in snowflake helper.
    else
    {
        /// Draw the Triangle - Recursively calls snowflake draw; current iteration will increment within.
        constructTriangle(top, leftPoint, rightPoint, sf::Color::Blue, graphic_window); // creates our initial triangle passed top, left, right, color, and window object
        /*recursive_koch_HELPER(leftPoint, rightPoint, 1, graphic_window); // draws left -> right line
        recursive_koch_HELPER(top, leftPoint, 1, graphic_window); // draws top -> left line
        recursive_koch_HELPER(rightPoint, top, 1, graphic_window); // draws right -> top line
*/
    }
}

void initiateSierpinski(int HEIGHT, int WIDTH, std::string fileName, sf::Color userColor) {

    //creates our object window using the template class RenderWindow. This accepts two parameters. A mode and a title.
    // The mode is an object of type VideoMode (template class of SFML library) which requires two parameters a Width and a Height. Used to scale the window's box.
    sf::RenderWindow graphic_window(sf::VideoMode(WIDTH, HEIGHT), "Koch's Snowflake");

    SierpinskiTriangle graphic; // creates an object of our Koch Snowflake class; calls the default constructor automatically.

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