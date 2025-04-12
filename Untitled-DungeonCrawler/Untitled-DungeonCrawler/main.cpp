#include <iostream>
#include "Enemy.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);
    Enemy temp;
    temp.getModel().setFillColor(sf::Color::Red);
    temp.getModel().setPosition(sf::Vector2f(0, 0));
    temp.getModel().setSize(sf::Vector2f(32, 32));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        //window.draw(shape);
        window.draw(temp.getModel());
        window.display();
    }
}