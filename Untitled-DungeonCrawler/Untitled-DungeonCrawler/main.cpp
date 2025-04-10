#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayBox.h"
#include <vector>

using std::cout;
using std::endl;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    std::vector<float> testVect;
    sf::RectangleShape object;
    RayCast testRay(200);

    PlayBox testBox;

    object.setSize(sf::Vector2f(100, 100));
    object.setPosition(sf::Vector2f(500, 500));
    object.setFillColor(sf::Color::Blue);

    testRay.setRayCoords();
    testBox.initialize();
    // draw it
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        testRay.updateRay(object, window, (sf::Vector2f)sf::Mouse::getPosition());
        //testBox.getVision().updateRay(object, window, testBox.getOrigin());

        window.clear();
        window.draw(object);
        window.draw(testBox);
        //testBox.getVision().rayCast(object, window, testBox.getOrigin());
        //testBox.rotate(sf::Angle(sf::degrees(10)));
        //testBox.rotateAll();
        testRay.rayCast(object, window, (sf::Vector2f)sf::Mouse::getPosition(window));
        window.display();
    }
}