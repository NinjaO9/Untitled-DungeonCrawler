#pragma once
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Obstacle.hpp"

using std::vector;

class LevelManager;

class GameManager
{
public:
	static GameManager*& getInstance()
	{
		if (!instance)
		{
			instance = new GameManager();
			lvl = nullptr;
			instance->initLevelManager();
		}
		return instance;
	}

	vector<Enemy*>& getEnemies();

	vector<Obstacle*>& getObstacles(); // Will have to replace 'Obstacle' with wall, eventually

	//Player*& getPlayer();  // Get the player instance

	sf::Vector2f& getMousePos(); // temp

	void setWindow(sf::Window& window);

	sf::Window*& getWindow();

	void updateMouse();

	void destroyManager();

	LevelManager*& getLevel();

	void initLevelManager();

private:
	static GameManager* instance;
	static LevelManager* lvl;

	sf::Window* activeWindow;
	// Player* playerInstance; // when we finally get the player class made, the game manager will hold a pointer to the player so that it can be accessed by anything
	sf::Vector2f mousePos; // temporary variable to test enemy functionality with chasing
	vector<Enemy*> enemyArr; // vector of enemies, can be used to iterate (specifically) through each enemy
	vector<Obstacle*> wallArr; // vector of walls, can be used to iterate (specifically) through each wall instance in a level. (Probably to check for collisions)
	

	GameManager() { activeWindow = nullptr; return; }
	GameManager(GameManager& newManager) = delete;
	GameManager& operator=(GameManager& oldManager) = delete;
	~GameManager() { return; }

};

