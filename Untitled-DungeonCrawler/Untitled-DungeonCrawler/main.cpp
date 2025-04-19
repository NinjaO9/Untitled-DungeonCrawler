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
    for (int i = 0; i < 20; i++) // initialize given number of entities 
    {
        gameManager->getEnemies().push_back(new Enemy(10, 200, 5, 10, sf::Vector2f(100,100))); // create a new enemy with default values
    }

    Obstacle* testObs = new Obstacle({ 200,200 });
    gameManager->getObstacles().push_back(testObs);
    while (window.isOpen())
    {
        window.clear();
        gameManager->updateMouse();
        //std::cout << gameManager->getMousePos().x << " , " << gameManager->getMousePos().y << std::endl;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::B)
                {
                    std::cout << "NEW OBSTACLE CREATED!" << std::endl;
                    gameManager->getObstacles().push_back(new Obstacle((sf::Vector2f)sf::Mouse::getPosition(window)));
                    std::cout << gameManager->getObstacles().size() << std::endl;
                }
            }
        }

        for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
        {
            enemy->update();
            window.draw(enemy->getModel());
            window.draw(enemy->getPatrolRay()); // NOTE2: PRINTING TO THE CONSOLE CAN ALSO BE A PREFORMANCE KILLER!
            window.draw(enemy->getPlayerRay()); // NOTE: DRAWING THE RAYS IS A PREFORMANCE KILLER! COMMENT THESE OUT BEFORE JUDGING GAME PREFORMANCE
        }

        for (Obstacle* obs : gameManager->getObstacles())
        {
            window.draw(obs->getModel());
        }
        window.display();
    }
    texManager->destroyManager();
    gameManager->destroyManager();
}