#pragma once
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Obstacle.hpp"

using std::vector;

class GameManager
{
public:
	static GameManager*& getInstance()
	{
		if (!instance)
		{
			instance = new GameManager();
		}
		return instance;
	}

	vector<Enemy*>& getEnemies();

	vector<Obstacle*>& getObstacles(); // Will have to replace 'Obstacle' with wall, eventually

	// Player*& getPlayer()/ // Get the player instance

	void destroyManager();

private:
	static GameManager* instance;
	// Player* playerInstance; // when we finally get the player class made, the game manager will hold a pointer to the player so that it can be accessed by anything
	vector<Enemy*> enemyArr; // vector of enemies, can be used to iterate (specifically) through each enemy
	vector<Obstacle*> wallArr; // vector of walls, can be used to iterate (specifically) through each wall instance in a level. (Probably to check for collisions)
	

	GameManager() { return; }
	GameManager(GameManager& newManager) = delete;
	GameManager& operator=(GameManager& oldManager) = delete;
	~GameManager() { return; }

};

