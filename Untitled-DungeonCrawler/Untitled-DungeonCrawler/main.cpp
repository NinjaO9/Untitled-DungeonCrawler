#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#define ENTITY_COUNT 20
int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    bool isPaused = false;

    TextureManager* texManager = TextureManager::getInstance();
    GameManager* gameManager = GameManager::getInstance();
    gameManager->setWindow(window);
    texManager->loadTextures("Textures.txt");  
    Growths inputGrowths[] = {
    Growths(90, 30, 40, 20, 10),
    Growths(60, 15, 25, 12, 5),
    Growths(50, 20, 15, 10, 0),
    Growths(70, 10, 30, 15, 3) //random filler values for now
    };
    Stats inputStats[] = {
     Stats(20, 1.2f, 4, 3, 15),
    Stats(12, 0.8f, 2, 1, 10),
    Stats(15, 0.6f, 1, 2, 8),
    Stats(10, 1.0f, 3, 0, 12) //same for stats; random filler, change to more appropriate values
    };
    Growths growthTable[ENTITY_COUNT];
    Stats statTable[ENTITY_COUNT];
    int inputCount = std::min((int)(sizeof(inputStats) / sizeof(Stats)), ENTITY_COUNT);
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (i < inputCount) {
            statTable[i] = inputStats[i];
            growthTable[i] = inputGrowths[i];
        }
        else {
            statTable[i] = defaultStatLine;
            growthTable[i] = defaultGrowths;
        }
        statTable[i].setGrowths(growthTable[i]);
    }
    gameManager->getPlayer().push_back(new Player(statTable[1]/*stats*/, growthTable[1]/*growths*/, 1/*lvl*/, sf::Vector2f(100, 100)));
    for (int i = 0; i < ENTITY_COUNT-1; i++) // initialize given number of entities 
    {
        gameManager->getEnemies().push_back(new Enemy(statTable[1]/*stats*/, growthTable[1]/*growths*/, 1/*lvl*/, 200/*viewdistance*/, 5/*attackrange*/, 2/*idletime*/, sf::Vector2f(100, 100)/*position*/)); // create a new enemy with default values
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