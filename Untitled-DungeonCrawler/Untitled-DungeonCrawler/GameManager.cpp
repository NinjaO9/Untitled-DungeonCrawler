#include "GameManager.hpp"
#include "LevelManager.hpp"


GameManager* GameManager::instance = nullptr;
LevelManager* GameManager::lvl = nullptr;

vector<Enemy*>& GameManager::getEnemies()
{
    return enemyArr;
}

sf::Vector2f& GameManager::getMousePos()
{
    return mousePos;
}

void GameManager::setWindow(sf::RenderWindow& window)
{
    activeWindow = &window;
}

sf::RenderWindow*& GameManager::getWindow()
{
    return activeWindow;
}

void GameManager::updateMouse()
{
    mousePos = activeWindow->mapPixelToCoords(sf::Mouse::getPosition(*activeWindow), windowView);
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

vector<Obstacle*> GameManager::getNearbyObstacles(sf::Vector2f pos)
{
    vector<Obstacle*> nearby;
    // this is going to be more like 'onscreen' but its ok

    for (Obstacle* wall : lvl->getTiles())
    {
        //cout << "Pre-conversion " << wall->getPos().x << " , " << wall->getPos().y;
        sf::Vector2f realVector = (sf::Vector2f)activeWindow->mapCoordsToPixel(wall->getPos() , activeWindow->getView());
        //cout << "Mid-conversion " << realVector.x << " , " << realVector.y << endl;
        //realVector = activeWindow->mapPixelToCoords((sf::Vector2i)realVector, activeWindow->getView());
        //cout << "Post-conversion " << realVector.x << " , " << realVector.y << endl;
        if (abs(realVector.length() - pos.length()) > 100) { continue; } // skip if not on screen
        nearby.push_back(wall);
    }

    return nearby;
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