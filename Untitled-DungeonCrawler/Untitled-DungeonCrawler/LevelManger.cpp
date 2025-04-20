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
}

void LevelManager::initGameManager()
{
	gm = GameManager::getInstance();
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
			//placeEmpty();
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
	levelTiles.push_back(new Obstacle((sf::Vector2f)placementSpot));

}

void LevelManager::placeWall()
{
	levelTiles.push_back(new Obstacle((sf::Vector2f)placementSpot));

}

void LevelManager::placeEnemy()
{
	gm->getEnemies().push_back(new Enemy(10, 200.0f, 5.0f, 2.0f, (sf::Vector2f)placementSpot));
}
