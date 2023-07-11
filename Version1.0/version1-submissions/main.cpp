//// This is the template for our basic user interface; upon completion of various versions of recursive graphic algorithms we will implement and call
//// the respective .cpp and .h files within the menu.

/////////////////// Libraries ////////////////////
#include <iostream>
#include <SFML/Graphics.hpp>
//////////////////////////////////////////////////
sf::CircleShape drawTriangle(sf::CircleShape triangle, int radius){
    if (radius < 10){
        //set condition to end recursive call
    }else{
        //create smaller triangles, alternate color
        //decrement radius

        //change triangle color to white
        drawTriangle(triangle, radius/2);
        //change new triangles to red

    }
    return triangle;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(640,480), "SFML Application");
//    sf::CircleShape shape;
//    shape.setRadius(100.f);
//    shape.setPosition(100.f, 150.f);
//    shape.setFillColor(sf::Color::Red);
    sf::CircleShape triangle(200, 3);
    triangle.setFillColor(sf::Color::Red);
    //set position to center


    //window size 1000x1000
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
//        window.draw(drawTriangle(triangle, 200));
        window.draw(triangle);
        window.display();
    }

}






////// Main Menu Display Function; passed a boolean to check if the intro message has yet to be displayed.
//void displayMainMenu(bool firstDisplay){
//    if (firstDisplay == false) {
//        std::cout << "\n\nWelcome to our project 212 user interface. Please read through following menu. \n" <<
//                     "Upon selection of your algorithm of choice you will be requested for input of the \n" <<
//                     "appropriate parameters required for the construction of the graphic. \n\n";
//    }
//    std::cout << "1.) Hilbert's Curve \n" <<
//                 "2.) Sierpinski's Triangle \n" <<
//                 "3.) Koch's Snowflake \n" <<
//                 "4.) TBD's Thing \n" <<
//                 "5.) End Program \n\n";
//}
//
//
////// Sub Menu Display Function; passed the main menu choice, to direct output.
//void displaySubMenu(int mainMenuChoice){
//    //// HILBERT'S CURVE - The messages and parameters are templates. Adjust to what is needed in future additions.
//    if (mainMenuChoice == 1){
//        std::cout << "Welcome to the Hilbert's Curve Algorithm \n" <<
//                     "Please enter a [Some Parameter] and a [Some Parameter] \n\n";
//    }
//    //// SIERPINSKI'S TRIANGLE
//    else if (mainMenuChoice == 2){
//        std::cout << "Welcome to the Sierpinski's Triangle Algorithm \n" <<
//                   "Please enter a [Some Parameter], [Some Parameter], and [Some Other Parameter] \n\n";
//
//    }
//        //// KOCH'S SNOWFLAKE
//    else if (mainMenuChoice == 3){
//        std::cout << "Welcome to the Koch's Snowflake Algorithm \n" <<
//                  "Please enter a [Some Parameter] and a [Some Parameter] \n\n";
//
//    }
//        //// 4TH ALGORITHM THING
//    else if (mainMenuChoice == 4){
//        std::cout << "Welcome to this thing we haven't decided yet \n" <<
//                     "Please enter [Whatever Parameter is needed] \n\n";
//    }
//}
//
////// Main function; Initiates program and starts the user interface, includes boolean catch to avoid reprinting intro message repeatedly.
//int main(){
//    bool firstDisplay; // boolean to stop Main menu from outputting introduction every time it's called.
//    displayMainMenu(firstDisplay);
//    firstDisplay = true; // flip boolean to prevent future introduction output.
//
//    //// MainMenuChoice determines selection of outer loop.
//    int mainMenuChoice = 666; //int variable to store outer loop choice. Set to a number outside of range.
//
//    //// Loop through until the user selects 5 to end the program.
//    while(mainMenuChoice != 5) {
//        int subMenuChoice = 666; //int variable to store the inner loops choices. Resets to number outside of range after each iteration of outer loop.
//
//        std::cout << "Please input the number of your choice: "; std::cin >> mainMenuChoice; std::cout << "\n"; //Request Menu Choice
//
//        //// HILBERT'S CURVE
//        if (mainMenuChoice == 1){
//            int param1, param2; // initialize necessary params for future function/class call from Hilbert files.
//            displaySubMenu(mainMenuChoice);
//            std::cout << "Enter [Some Parameter 1]: "; std::cin >> param1;
//            std::cout << "Enter [Some Parameter 2]: "; std::cin >> param2;
//
//            /// TODO: INSERT APPROPRIATE OBJ CREATION OR FUNCTION CALLS TO *** HILBERT ALG *** USING PARAMS.
//            // Stuff Goes Here.
//        }
//        //// SIERPINSKI'S TRIANGLE
//        else if (mainMenuChoice == 2){
//            int param1, param2, param3; // initialize necessary params for future function/class call from Sierpinski files.
//            displaySubMenu(mainMenuChoice);
//            std::cout << "Enter [Some Parameter 1]: "; std::cin >> param1;
//            std::cout << "Enter [Some Parameter 2]: "; std::cin >> param2;
//            std::cout << "Enter [Some Parameter 3]: "; std::cin >> param3;
//
//            /// TODO: INSERT APPROPRIATE OBJ CREATION OR FUNCTION CALLS TO *** SIERPINSKI ALG *** USING PARAMS.
//            // Stuff Goes Here.
//        }
//        //// KOCH'S SNOWFLAKE
//        else if (mainMenuChoice == 3){
//            int param1, param2; // initialize necessary params for future function/class call from Koch files.
//            displaySubMenu(mainMenuChoice);
//            std::cout << "Enter [Some Parameter 1]: "; std::cin >> param1;
//            std::cout << "Enter [Some Parameter 2]: "; std::cin >> param2;
//
//            /// TODO: INSERT APPROPRIATE OBJ CREATION OR FUNCTION CALLS TO *** KOCH ALG *** USING PARAMS.
//            // Stuff Goes Here.
//        }
//        //// 4TH ALGORITHM THING
//        else if (mainMenuChoice == 4){
//            int param1; // intialize necessary params for future function/class calls within the undecided algorithm files.
//            displaySubMenu(mainMenuChoice);
//            std::cout << "Enter [Some Parameter 1]: "; std::cin >> param1;
//
//            /// TODO: INSERT APPROPRIATE OBJ CREATION OR FUNCTION CALLS TO *** MYSTERY ALG *** USING PARAMS.
//            // Stuff Goes Here.
//        }
//        //// TERMINATE PROGRAM - END OUTER WHILE
//        else if (mainMenuChoice == 5){
//            std::cout << "Program is ending... Thank you!\n\n";
//            break;
//        }
//        else{
//            std::cout << "Enter an appropriate number between 1 and 5. \n\n";
//        }
//
//        displayMainMenu(firstDisplay); //if while loop is not broke within elif #5... display menu for next selection.
//    }
//}