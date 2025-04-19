#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#include "Weapon.hpp"

int main()
{
    Weapon testW;

    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    bool isPaused = false;

    TextureManager* texManager = TextureManager::getInstance();
    GameManager* gameManager = GameManager::getInstance();
    texManager->loadTextures("Textures.txt");
    for (int i = 0; i < 5; i++) // initialize given number of entities (100 is really laggy, 50 is kinda laggy, 25 is somewhat of a sweetspot
    {
        gameManager->getEnemies().push_back(new Enemy()); // create a new enemy with default values
    }
   
    while (window.isOpen())
    {
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
        {
            enemy->update();
            window.draw(enemy->getModel());
        }
        window.display();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
           testW.BaseWeaponATK(5);   
        }
    }
    texManager->destroyManager();
    gameManager->destroyManager();
}