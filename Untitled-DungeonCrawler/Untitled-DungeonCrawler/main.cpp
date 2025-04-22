#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#include "LevelManager.hpp"
#include <fstream>

#define RUN_DEBUG true
#define TEST_CASE 0

using std::fstream;

void runGame(); // defined in main because (i dont have a good reason, I just wanted to split up the main() function into two smaller - 'testcase/debug' and 'rungame' functions)
void runDEBUG();

int main()
{
    srand(time(NULL));

    if (RUN_DEBUG)
    {
        cout << "NOTICE: You are running DEBUG/TEST_CASE mode! - Test case being played: " << TEST_CASE << endl;
        runDEBUG();
    }
    else
    {
        runGame();
    }

}

void runGame()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "GAME RUNNING");
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

        if (frameClock.getElapsedTime().asMilliseconds() > 15) // Tested values: 15 - 60 FPS; 27 - ~33 FPS
        {
            window.setView(gameManager->getView());
            window.clear();
            for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
            {
                float realX = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).x;
                float realY = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).y;
                if (realX < 0 || realX > window.getSize().x) { continue; } // skip updating any enemy that is out of view
                enemy->update();
                window.draw(enemy->getModel());
                window.draw(enemy->getPatrolRay()); // NOTE2: PRINTING TO THE CONSOLE CAN ALSO BE A PREFORMANCE KILLER!
                window.draw(enemy->getPlayerRay()); // NOTE: DRAWING THE RAYS IS A PREFORMANCE KILLER! COMMENT THESE OUT BEFORE JUDGING GAME PREFORMANCE

            }
            for (Obstacle* obs : lvl->getTiles())
            {
                window.draw(obs->getModel());
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

    }
}

void runDEBUG()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "DEBUG MODE - TEST CASES");
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

    frameClock.start();

    Obstacle testWall({ 100,100 });
    Enemy testEnemy(10, 200, 5, 2, { 300,100 });
    gameManager->getLevel()->getTiles().push_back(&testWall);
    gameManager->getEnemies().push_back(&testEnemy);

    switch (TEST_CASE)
    {
    case 0:
        cout << "TEST_CASE description: Testing enemy target logic - the enemy is going to have a target position at a spawned wall. The enemy should check if the position is valid, (and thus determine the position is invalid) and determine a new location to go (this will be random) " << endl;
        testEnemy.getTargetPos() = testWall.getPos(); 
        testEnemy.checkForcedPos(); // only call the check once to prevent lag from not-needed constant checks
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            if (frameClock.getElapsedTime().asMilliseconds() > 15) // frame-rate limiter
            {
                window.clear();
                testEnemy.update();
                window.draw(testWall.getModel());
                window.draw(testEnemy.getModel());
                window.draw(testEnemy.getPatrolRay());
                window.display();
                frameClock.restart();

            }
            cout << "Working" << endl;
        }
        break;
    case 1:
        cout << "TEST_CASE description: Testing enemy attack / chase logic - the enemy will have a target position at a dummy player. Once the enemy gets close enough to the player, the enemy will start going quickly towards the dummy player, and once in a suitable range, will start flashing blue to indicate attacking." << endl;
        testEnemy.getTargetPos(); // = dummyPlayerPos; //testWall.getPos();
        testEnemy.checkForcedPos(); // only call the check once to prevent lag from not-needed constant checks
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            if (frameClock.getElapsedTime().asMilliseconds() > 15) // frame-rate limiter
            {
                window.clear();
                testEnemy.update();

                window.display();
                frameClock.restart();

            }
            cout << "Working" << endl;
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        cout << "Invalid TEST_CASE number!: " << TEST_CASE << " > max(4) - Edit line 10 within main.cpp and re-run to try again." << endl;
        break;
    }

    texManager->destroyManager();
    gameManager->destroyManager();
}
