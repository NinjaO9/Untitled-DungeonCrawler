#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    bool isPaused = false;

    TextureManager* texManager = TextureManager::getInstance();
    GameManager* gameManager = GameManager::getInstance();
    gameManager->setWindow(window);
    texManager->loadTextures("Textures.txt");
    for (int i = 0; i < 100; i++) // initialize given number of entities 
    {
        gameManager->getEnemies().push_back(new Enemy()); // create a new enemy with default values
    }
   
    while (window.isOpen())
    {
        window.clear();
        gameManager->updateMouse();
        //std::cout << gameManager->getMousePos().x << " , " << gameManager->getMousePos().y << std::endl;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
        {
            enemy->update();
            window.draw(enemy->getModel());
            window.draw(enemy->getPlayerRay()); // NOTE: DRAWING THE RAYS IS A PREFORMANCE KILLER! COMMENT THESE OUT BEFORE JUDGING GAME PREFORMANCE
            window.draw(enemy->getPatrolRay());
        }
        window.display();
    }
    texManager->destroyManager();
    gameManager->destroyManager();
}