#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#include "LevelManager.hpp"
#include <fstream>

using std::fstream;

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