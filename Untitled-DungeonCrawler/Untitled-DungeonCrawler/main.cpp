#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include <vector>
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    std::vector<float> testVect;
    sf::RectangleShape object;
    Ray testRay(200);

    object.setSize(sf::Vector2f(10, 10));
    object.setPosition(sf::Vector2f(500, 500));
    object.setFillColor(sf::Color::Blue);

    testRay.setRayCoords();
    // draw it
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        testRay.updateRay(object, window);

        window.clear();
        window.draw(object);
        testRay.displayRay(window);
        //testRay.rayCast(object, window);
        window.display();
    }
}