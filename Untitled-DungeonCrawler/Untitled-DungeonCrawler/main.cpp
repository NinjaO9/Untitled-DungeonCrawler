#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#include "LevelManager.hpp"
#include <fstream>

using std::fstream;

#define ENTITY_COUNT 20 // NOTE FROM DAVID -> keep in mind that the entity count is (kinda) random per level, it depends on how many enemies whoever decides to make the levels chooses to put in
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");

    bool isPaused = false;
    int frameCount = 0, frameRate = 0;

    TextureManager* texManager = TextureManager::getInstance();
    GameManager* gameManager = GameManager::getInstance();
    LevelManager* lvl = gameManager->getLevel();
    sf::Clock frameClock;
    fstream file;

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



    gameManager->getView().zoom(0.5);

    file.open("Level1.txt");
    lvl->loadFromFile(file);
    file.close();
    gameManager->getClock().start();
    frameClock.start();

    while (window.isOpen())
    {
        if (gameManager->getClock().getElapsedTime().asSeconds() > 1)
        {
            frameRate = frameCount;
            cout << frameRate << endl;
            gameManager->getClock().reset();
            frameCount = 0;
            gameManager->getClock().start();
        }

        gameManager->updateMouse();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (frameClock.getElapsedTime().asMilliseconds() > 15) // Tested values: 15 - ~60 FPS; 27 - ~33 FPS
        {
            window.setView(gameManager->getView());
            window.clear();
            for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
            {
                float realX = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).x;
                float realY = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).y;
                if (realX < 0 || realX > window.getSize().x) { continue; } // skip updating any enemy that is out of view
                else if (realY < 0 || realY > window.getSize().y) { continue; }
                enemy->update();
                window.draw(enemy->getModel());
                window.draw(enemy->getPatrolRay()); // NOTE2: PRINTING TO THE CONSOLE CAN ALSO BE A PREFORMANCE KILLER!
                window.draw(enemy->getPlayerRay()); // NOTE: DRAWING THE RAYS IS A PREFORMANCE KILLER! COMMENT THESE OUT BEFORE JUDGING GAME PREFORMANCE

            }
            for (Obstacle* obs : lvl->getTiles())
            {
                window.draw(obs->getModel());
            }
            if (lvl->getExitTile())
            {
                window.draw(lvl->getExitTile()->getModel());
            }
            window.display();
            frameCount++;
            frameClock.restart();
        }

        // temp stuff until we get player done; camera will likely follow player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        {
            gameManager->getView().move({ -0.001,0 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        {
            gameManager->getView().move({ 0.001,0 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        {
            gameManager->getView().move({ 0,-0.001 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        {
            gameManager->getView().move({ 0,0.001 });
        }
        if (gameManager->getLevel()->getExitTile() && gameManager->getLevel()->getExitTile()->getModel().getGlobalBounds().contains(gameManager->getMousePos())) // is the 'player' at the exit tile?
        {
            gameManager->getLevel()->unloadLevel();
            file.open("Level2.txt");
            window.setView(window.getDefaultView());
            gameManager->getLevel()->loadFromFile(file);
            file.close();
        }

    }
    texManager->destroyManager();
    gameManager->destroyManager();
}