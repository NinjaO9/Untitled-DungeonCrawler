#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class GameManager;

class LevelManager
{
public:

	LevelManager()
	{
		placementSpot = sf::Vector2i(0, 0);
		initGameManager();
	}

	~LevelManager()
	{

	}

	std::vector<Obstacle*>& getTiles()
	{
		return wallTiles;
	}

	void loadFromFile(std::fstream& file);

	Obstacle*& getExitTile();

	void unloadLevel();

	void initGameManager();

	void setPlayerPosition();

private:
	static GameManager* gm;
	std::vector<Obstacle*> wallTiles;
	Obstacle* exitTile;
	int const size = 32; // keep a constant 32 sprite size (this would be moved to another class)

	/* These should have their own class or struct (or be defined in a higher class */

	sf::Texture emptyTexture;
	sf::Texture wallTexture;

	sf::Vector2i placementSpot;

	void generateLayer(std::string line);

	void placeEmpty();

	void placeWall();

	void placeEnemy(int n);//n should be at least 1 but at most the number unique enemies we've loaded so far (all this can be seen in Stats.hpp

	void placeExit();

	void placeBoss();

};