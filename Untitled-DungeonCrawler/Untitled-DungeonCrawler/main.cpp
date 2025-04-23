#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"
#include "Weapon.hpp"
#include "LevelManager.hpp"
#include <fstream>

#define RUN_DEBUG false // Replace 'false' with 'true' to run debug mode, running the test case below:
#define TEST_CASE 4 // from a range of (0-4) it will run a specific test case. Keep in mind that the test case will do what it is meant to do, but it won't end the program. The user must close the window to end the test
#define ENTITY_COUNT 20 // Note from David -> Level gen takes care of enemy spawning, so we may or may not be able to use anything that rewuires an 'entity coutn' variable. let me know what youre trying to do and we can try to figure it out with the current level gen program

using std::fstream;

void runGame(); // defined in main because (i dont have a good reason, I just wanted to split up the main() function into two smaller - 'testcase/debug' and 'rungame' functions)
void runDEBUG();

int main()
{
    srand(time(NULL));

    if (RUN_DEBUG)
    {
        cout << "NOTICE: You are running DEBUG/TEST_CASE mode! - Test cases do not end on their own, however they are meant to behave in an expected way for the duration of the test as it is described in the text that follows -  Test case being played: " << TEST_CASE << endl;
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
    Weapon testW; Sword sword;
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
    //for (int i = 0; i < ENTITY_COUNT-1; i++) // initialize given number of entities 
    //{
    //    gameManager->getEnemies().push_back(new Enemy(statTable[1]/*stats*/, growthTable[1]/*growths*/, 1/*lvl*/, 200/*viewdistance*/, 5/*attackrange*/, 2/*idletime*/, sf::Vector2f(100, 100)/*position*/)); // create a new enemy with default values
    //}



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

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                    testW.BaseWeaponATK(sword.getBaseDMG());
            }

        }

        if (frameClock.getElapsedTime().asMilliseconds() > 15) // Tested values: 15 - ~60 FPS; 27 - ~33 FPS
        {
            window.setView(gameManager->getView());
            window.clear();
            gameManager->getPlayer()->update();
            gameManager->getView().setCenter(gameManager->getPlayerPos());
            for (Enemy* enemy : gameManager->getEnemies()) // feel free to delete if you need to do something else with drawing and the enemies get annoying
            {
                float realX = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).x;
                float realY = window.mapCoordsToPixel(enemy->getPos(), gameManager->getView()).y;
                if (realX < 0 || realX > window.getSize().x) { continue; } // skip updating any enemy that is out of view
                else if (realY < 0 || realY > window.getSize().y) { continue; }
                enemy->update();
                window.draw(enemy->getModel());
                //window.draw(enemy->getPatrolRay()); // NOTE2: PRINTING TO THE CONSOLE CAN ALSO BE A PREFORMANCE KILLER!
                //window.draw(enemy->getPlayerRay()); // NOTE: DRAWING THE RAYS IS A PREFORMANCE KILLER! COMMENT THESE OUT BEFORE JUDGING GAME PREFORMANCE

            }
            window.draw(gameManager->getPlayer()->getModel());
            for (Obstacle* obs : lvl->getTiles())
            {
                window.draw(obs->getModel());
            }
            if (lvl->getExitTile())
            {
                window.draw(lvl->getExitTile()->getModel());

            }
            window.draw(gameManager->getPlayer()->getModel());
            if (gameManager->getLevel()->getExitTile() && gameManager->getLevel()->getExitTile()->getModel().getGlobalBounds().contains(gameManager->getPlayerPos())) // is the 'player' at the exit tile?
            {
                gameManager->getLevel()->unloadLevel();
                window.setView(window.getDefaultView());
                gameManager->getLevel()->loadSavedNext();
                file.close();
            }
            window.display();
            frameCount++;
            frameClock.restart();
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
    gameManager->getLevel()->getTiles().push_back(new Obstacle({100,100}));
    Obstacle dummyPlayer({ 50,100 });
    sf::VertexArray PlayerRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
    dummyPlayer.getModel().setColor(sf::Color::Red);
    gameManager->getEnemies().push_back(new Enemy(defaultStatLine,defaultGrowths, 1, 200, 32, 0, {300,100}));

    switch (TEST_CASE)
    {
    case 0:
        cout << "TEST_CASE description: Testing enemy target logic - the enemy is going to have a target position at a spawned wall. The enemy should check if the position is valid, (and thus determine the position is invalid) and determine a new location to go (this will be random) " << endl;
        gameManager->getEnemies()[0]->getTargetPos() = lvl->getTiles()[0]->getPos();  // IMPORTANT: Setting the target position to the wall
        gameManager->getEnemies()[0]->checkForcedPos(); // only call the check once to prevent lag from not-needed constant checks - forcing the enemy to check the target position. (The reason we must call this manually is because the enemy should normally check for a valid location before actually selecting a target position)
        // in essence, this test case just goes through the normal process the update() function would naturally cause, assuming the enemy has a valid starting target (hardcoded as its starting point)
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
                gameManager->getEnemies()[0]->update();
                window.draw(lvl->getTiles()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getPatrolRay());
                window.display();
                frameClock.restart();

            }
        }
        break;
    case 1:
        cout << "TEST_CASE description: Testing enemy attack / chase logic - the enemy will have a target position at a dummy player. Once the enemy gets close enough to the player, the enemy will start going quickly towards the dummy player, and once in a suitable range, will start flashing blue to indicate attacking." << endl;
        gameManager->getEnemies()[0]->getTargetPos() = dummyPlayer.getPos(); // IMPORTANT: Setting the target position to the wall
        lvl->getTiles().clear();
        gameManager->setMousePos({ dummyPlayer.getModel().getPosition().x + 3, dummyPlayer.getModel().getPosition().y });

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
                gameManager->getEnemies()[0]->update();
                window.draw(dummyPlayer.getModel());
                window.draw(gameManager->getEnemies()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getPatrolRay());
                window.display();
                frameClock.restart();
            }
        }
        break;
    case 2:
        
        cout << "TEST_CASE description: Testing enemy collision logic - The enemy will constantly move into a wall, colliding and bouncing back. In this case, ending up at the top left of the wall is a predicted behavior because of the nature of the checkCollision() function." << endl;
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
                gameManager->getEnemies()[0]->getModel().move({ -1,0 });
                gameManager->getEnemies()[0]->checkCollision();

                window.draw(lvl->getTiles()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getPatrolRay());

                window.display();

                frameClock.restart();
            }
        }
        break;
    case 3:
        cout << "TEST_CASE description: Testing enemy LOS logic (line of sight) - The enemy will display a ray that connects to the player, however it is blocked by a wall. Thus, it will display red at the player to signify that the player cannot be seen. The wall will be removed and then the ray will turn green to simulate the enemy seeing the player " << endl;
        gameManager->getEnemies()[0]->getTargetPos() = dummyPlayer.getModel().getPosition();
        gameManager->setMousePos({ dummyPlayer.getModel().getPosition().x + 3, dummyPlayer.getModel().getPosition().y });
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            if (frameClock.getElapsedTime().asMilliseconds() > 15) // frame-rate limiter
            {
                frameCount++;
                window.clear();
                gameManager->getEnemies()[0]->getModel().setPosition({ 150,110 }); // for the sake of this test, the enemy is staying in the same place
                gameManager->getEnemies()[0]->update();
                if (frameCount == 60)
                {
                    lvl->getTiles().clear();
                }

                if (frameCount < 60)
                {
                    window.draw(lvl->getTiles()[0]->getModel());
                }
                window.draw(dummyPlayer.getModel());
                window.draw(gameManager->getEnemies()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getPlayerRay());

                window.display();

                frameClock.restart();
            }
        }
        break;
    case 4:
        cout << "TEST_CASE description: Testing enemy stopping-chase handling - The enemy will be chasing a dummy player, however the player will outspeed the enemy, which should cause the enemy to lose interest in the player, and inturn find a new place to go. NOTE: Red indicates the enemy doesnt 'see' the player, Green indicates that the enemy can and is pursuing the player" << endl;
        gameManager->getEnemies()[0]->getModel().setPosition({ 150,110 });
        gameManager->getEnemies()[0]->setPos(gameManager->getEnemies()[0]->getModel().getPosition());
        gameManager->getEnemies()[0]->getTargetPos() = dummyPlayer.getModel().getPosition();
        gameManager->setMousePos({ dummyPlayer.getModel().getPosition().x + 3, dummyPlayer.getModel().getPosition().y });
        lvl->getTiles().clear(); // no wall to prevent enemy from seeing dummy player

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            if (frameClock.getElapsedTime().asMilliseconds() > 15) // frame-rate limiter
            {
                frameCount++;
                window.clear();
                gameManager->getEnemies()[0]->update();
                dummyPlayer.getModel().move({ 0,4 }); // go down, the enemy should follow
                gameManager->setMousePos({ dummyPlayer.getModel().getPosition().x + 3, dummyPlayer.getModel().getPosition().y });
 
                window.draw(dummyPlayer.getModel());
                window.draw(gameManager->getEnemies()[0]->getModel());
                window.draw(gameManager->getEnemies()[0]->getPatrolRay());
                window.draw(gameManager->getEnemies()[0]->getPlayerRay());

                window.display();

                frameClock.restart();
            }
        }
        break;
    default:
        cout << "Invalid TEST_CASE number!: " << TEST_CASE << " > max(4) - Edit line 10 within main.cpp and re-run to try again." << endl;
        break;
    } // Switch case which contains all the debug test cases

    texManager->destroyManager();
    gameManager->destroyManager();
}
