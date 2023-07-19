#include "sierpinskitriangle.h"


void initiateSierpinski(int HEIGHT, int WIDTH, std::string fileName, sf::Color userColor)
{
    //creates our object window using the template class RenderWindow. This accepts two parameters. A mode and a title.
    // The mode is an object of type VideoMode (template class of SFML library) which requires two parameters a Width and a Height. Used to scale the window's box.
    sf::RenderWindow graphic_window(sf::VideoMode(WIDTH, HEIGHT), "Koch's Snowflake");

    int stage = 5;

    sierpinskiTriangle graphic; // creates an object of our Koch Snowflake class; calls the default constructor automatically.
    graphic.setInvisibleBox(0.0, 0.0, WIDTH, HEIGHT); // Snowflake Class setter - sets the dimensions of our invisible box in which the snowflake will be constructed; passed Width / Height from functions params.
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

        graphic.construct_triangle(graphic_window); // Snowflake Class Method - calls the method used to start actually drawing our snowflake; passed the window object.
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
