#pragma once
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Obstacle.hpp"
#include "Player.hpp"

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

	Player*& getPlayer();  // Get the player instance

	sf::Vector2f& getPlayerPos();

	void setMousePos(sf::Vector2f pos);

	sf::View& getView() { return windowView; }

	sf::Clock& getClock() { return gameClock; }

	void setWindow(sf::RenderWindow& window);

	sf::RenderWindow*& getWindow();

	void updateMouse();

	void destroyManager();

	LevelManager*& getLevel();

	void initLevelManager();

	vector<Obstacle*> getNearbyObstacles(sf::Vector2f pos);

private:
	static GameManager* instance;
	static LevelManager* lvl; // pointer to current level

	sf::RenderWindow* activeWindow;
	sf::View windowView;
	sf::Clock gameClock;
	Player* playerInstance; // when we finally get the player class made, the game manager will hold a pointer to the player so that it can be accessed by anything
	sf::Vector2f playerPos; // variable that can allow us to manipulate what is defined as the player
	vector<Enemy*> enemyArr; // vector of enemies, can be used to iterate (specifically) through each enemy

	GameManager() { activeWindow = nullptr; return; }
	GameManager(GameManager& newManager) = delete;
	GameManager& operator=(GameManager& oldManager) = delete;
	~GameManager() { return; }

};

