#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayBox.h"
#include "Level.hpp"
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
    Level level;
    std::fstream infile;
    infile.open("TestLevel.txt", std::ios::in);
    level.loadFromFile(infile);
    std::vector<sf::Sprite> levelTiles = level.getTiles();

    PlayBox testBox;
    sf::Texture empty;
    sf::Sprite testSpr(empty);
    empty.loadFromFile("Wall.png");

    object.setSize(sf::Vector2f(100, 100));
    object.setPosition(sf::Vector2f(500, 500));
    object.setFillColor(sf::Color::Blue);

    testSpr.setTexture(empty);

    testRay.setRayCoords();
    testBox.initialize();
    // draw it
    sf::View view;
    view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    view.setCenter(sf::Vector2f(500, 500));
    view.zoom(0.5);

    while (window.isOpen())
    {
        //window.setView(view);
        // define a centered viewport, with half the size of the window
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        ////testBox.getVision().updateRay(object, window, testBox.getOrigin());

        window.clear();
       // window.draw(object);
        window.draw(testSpr);
        //window.draw(testBox);
        //testBox.getVision().rayCast(object, window, testBox.getOrigin());
        //testBox.rotate(sf::Angle(sf::degrees(10)));
        //testBox.rotateAll();

        for (sf::Sprite& tile : levelTiles)
        {
            window.draw(tile);
        }
        testRay.updateRay(levelTiles, window, (sf::Vector2f)sf::Mouse::getPosition());
        testRay.rayCast(levelTiles, window, (sf::Vector2f)sf::Mouse::getPosition(window));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        {
            view.move(sf::Vector2f(-1, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        {
            view.move(sf::Vector2f(0, 1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        {
            view.move(sf::Vector2f(0, -1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        {
            view.move(sf::Vector2f(1, 0));
        }
        
        window.display();
    }
}