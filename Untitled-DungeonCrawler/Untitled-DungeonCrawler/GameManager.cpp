#include "GameManager.hpp"


GameManager* GameManager::instance = nullptr;

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

/* Remove the comment blocks when player finally gets added

Player*& GameManger::getPlayer()
{
    return playerInstance;
}

*/