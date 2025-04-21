#include "GameManager.hpp"
#include "LevelManager.hpp"


GameManager* GameManager::instance = nullptr;
LevelManager* GameManager::lvl = nullptr;

vector<Enemy*>& GameManager::getEnemies()
{
    return enemyArr;
}

vector<Obstacle*>& GameManager::getObstacles()
{
    return wallArr;
}

sf::Vector2f& GameManager::getMousePos()
{
    return mousePos;
}

void GameManager::setWindow(sf::Window& window)
{
    activeWindow = &window;
}

sf::Window*& GameManager::getWindow()
{
    return activeWindow;
}

void GameManager::updateMouse()
{
    mousePos = (sf::Vector2f)sf::Mouse::getPosition(*activeWindow);
}

void GameManager::destroyManager()
{
    delete instance;
    instance = nullptr;
}

void GameManager::initLevelManager()
{
    lvl = new LevelManager();
}

LevelManager*& GameManager::getLevel()
{
    return lvl;
}

/* Remove the comment blocks when player finally gets added

Player*& GameManger::getPlayer()
{
    return playerInstance;
}

*/