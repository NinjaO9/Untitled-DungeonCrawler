#include "LevelManager.hpp"
#include "GameManager.hpp"

GameManager* LevelManager::gm = nullptr;

void LevelManager::loadFromFile(std::fstream& file)
{
	char cStr[101]; // 100 * 32 = 3200 pixels length (+1 for null char)
	std::string line;
	int length = 0;
	while (!file.eof())
	{
		file.getline(cStr, 101);
		line = cStr;
		length = line.length();
		generateLayer(line);
		placementSpot += sf::Vector2i(-length * size, 32); // go back to the left, and one row down
	}
	placementSpot = sf::Vector2i(0, 0);
	if (exitTile != nullptr) { wallTiles.push_back(exitTile); } // forcing the exitTile to be at the end of the vector for easy calling (we should just use the pointer reference though)
	else { cout << "WARNING: This level has no exit tile! (*)" << endl; }
	// if we dont have an exit tile, then.... idk
}

Obstacle*& LevelManager::getExitTile()
{
	return exitTile;
}

void LevelManager::unloadLevel()
{
	for (Obstacle* wall : getTiles())
	{
		delete wall;
	}
	wallTiles.clear();
	exitTile = nullptr; // no need to delete exitTile because it was already deleted within the for range loop
	for (Enemy* enemy : gm->getEnemies())
	{
		delete enemy;
	}
	gm->getEnemies().clear();
}

void LevelManager::initGameManager()
{
	gm = GameManager::getInstance();
}

void LevelManager::setPlayerPosition()
{
	gm->getView().setCenter((sf::Vector2f)placementSpot);
	gm->getPlayer()->setPos((sf::Vector2f)placementSpot);
}

void LevelManager::handlePlayerSpawn()
{
	if (gm->getPlayer())
	{
		setPlayerPosition();
	}
	else
	{
		gm->getPlayer() = new Player(Stats(20, 2.3f, 4, 3, 15)/*stats*/, Growths(90, 30, 40, 20, 10)/*growths*/, 1/*lvl*/, (sf::Vector2f)placementSpot);
		// stats and growths were copied from main.cpp
	}
}

void LevelManager::generateLayer(std::string line)
{
	int index = 0;
	while (line[index] != '\0')
	{
		switch (line[index]) // Check out an ASCII table and make more cases in order to add different tile types
		{
		case 61: // A wall is in text | denoted by: =
			//std::cout << " |WALL|";
			placeWall();
			break;
		case 32: // An empty tile | denoted by: (space)
			//std::cout << "       ";
			//placeEmpty();
			break;
		case 66: // boss spawn | denoted by: B 
			//std::cout << "|BOSS| ";
			//placeEmpty();
			break;
		case 69:
			placeEnemy();
			break;
		case 83: // player spawn | denoted by: S
			//std::cout << "|SPAWN|";
			handlePlayerSpawn();
			break;
		case 42: // Exit level / enter next level | denoted by: *
			placeExit();
			break;
		default:
			break;
		}
		placementSpot += sf::Vector2i(32, 0); // move 32 to the right
		index++;
	}
	//std::cout << std::endl;
}

void LevelManager::placeEmpty()
{
	//wallTiles.push_back(new Obstacle((sf::Vector2f)placementSpot));

}

void LevelManager::placeWall()
{
	wallTiles.push_back(new Obstacle((sf::Vector2f)placementSpot));

}

void LevelManager::placeEnemy()
{
	gm->getEnemies().push_back(new Enemy(defaultStatLine, defaultGrowths,1, 200.0f, 5.0f, 2.0f, (sf::Vector2f)placementSpot));
}

void LevelManager::placeExit()
{
	exitTile = new Obstacle((sf::Vector2f)placementSpot);
	exitTile->getModel().setColor(sf::Color::Red); // temp color to help differentiate an exit tile from other tiles
}
