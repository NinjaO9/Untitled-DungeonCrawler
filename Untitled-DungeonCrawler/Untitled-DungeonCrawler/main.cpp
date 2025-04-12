#include <iostream>
#include "Enemy.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);
    Enemy temp(10, 50.0f, 5.0f, 10.0f, sf::Vector2f(300,300));
    Enemy temp2(20, 50.0f, 5.0f, 10.0f, sf::Vector2f(200,200));
   

    while (window.isOpen())
    {
        temp.update();
        temp2.update();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        //window.draw(shape);
        window.draw(temp.getModel());
        window.draw(temp2.getModel());
        window.display();
    }
}