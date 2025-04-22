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

void GameManager::setMousePos(sf::Vector2f pos)
{
    mousePos = pos;
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

// testing for possible optimization
vector<Obstacle*> GameManager::getNearbyObstacles(sf::Vector2f pos)
{
    vector<Obstacle*> nearby;
    // this is going to be more like 'onscreen' but its ok

    for (Obstacle* wall : lvl->getTiles())
    {
        //cout << "Pre-conversion " << wall->getPos().x << " , " << wall->getPos().y;
        //sf::Vector2f realVector = (sf::Vector2f)activeWindow->mapCoordsToPixel(wall->getPos() , activeWindow->getView());
        //cout << "Mid-conversion " << realVector.x << " , " << realVector.y << endl;
        //realVector = activeWindow->mapPixelToCoords((sf::Vector2i)realVector, activeWindow->getView());
        //cout << "Post-conversion " << realVector.x << " , " << realVector.y << endl;
        if (abs(abs(wall->getPos().length()) - abs(pos.length())) > 200) { continue; } // skip if not on screen
        else { wall->getModel().setColor(sf::Color::Red); }
        //else { cout << "{ " << realVector.x << "," << realVector.y << " } Diff: " << realVector.length() - pos.length() << " funcDiff: " << sqrt((realVector.x - pos.x) * (realVector.x - pos.x) + (realVector.y - pos.y) * (realVector.y - pos.y)) << endl; wall->getModel().setColor(sf::Color::Red); }
        nearby.push_back(wall);
    }
    cout << nearby.size() << endl;
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