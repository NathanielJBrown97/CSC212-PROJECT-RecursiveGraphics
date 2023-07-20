#ifndef CSC212_PROJECT_2_HCURVE_H
#define CSC212_PROJECT_2_HCURVE_H
#include <vector>
#include <SFML/Graphics.hpp>

class hCurve{
private:
    ////////// private member variables //////////////////////////////////
    float topright;
    float topleft;
    float bottomleft;
    float bottomright;
    // Order of the curve generation, represents how many times we will be recursively generating/calling the algorithm from points.
    int order;
    // The initial size of the grid, used to represent the grid size by (size x size) length x height.
    float size;
    sf::Color colorGraphic;
public:
    sf::RectangleShape invisible_box;
    // Default constructor // Parameters are necessary.
    hCurve();
    // Deconstructor.
    ~hCurve();

    // Getter Functions.
    int getOrder();
    float getSize();

    // Setter Functions.
    void setOrder(int order);
    void setSize(float size);
    // generates and returns the curve
    sf::Vector2f generateCurve(int order, float size, sf::Vector2f currentCoord, int travrseDir);
    void drawGraphic(sf::RenderWindow& graphic_window);
    std::vector<sf::Vector2f> coordinates;

//    void setColor(const sf::Color& color);
    int drawCup(sf::Vector2f currentPos, int direction);

    sf::Vector2f drawHilbertCurve(int order, int direction, sf::Vector2f currentCoord);
};


#endif //CSC212_PROJECT_2_HCURVE_H
