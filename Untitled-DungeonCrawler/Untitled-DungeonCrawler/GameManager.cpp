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

void GameManager::destroyManager()
{
    delete instance;
}

/* Remove the comment blocks when player finally gets added

Player*& GameManger::getPlayer()
{
    return playerInstance;
}

*/