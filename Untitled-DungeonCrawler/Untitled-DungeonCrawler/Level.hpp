#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class Level
{
public:

	Level()
	{
		emptyTexture.loadFromFile("Empty.png");
		wallTexture.loadFromFile("Wall.png");
		placementSpot = sf::Vector2i(0, 0);
	}

	~Level()
	{

	}

	std::vector<sf::Sprite>& getTiles()
	{
		return levelTiles;
	}

	void loadFromFile(std::fstream& file);

private:
	
	std::vector<sf::Sprite> levelTiles;
	int const size = 32; // keep a constant 32 sprite size (this would be moved to another class)

	/* These should have their own class or struct (or be defined in a higher class */

	sf::Texture emptyTexture;
	sf::Texture wallTexture;

	sf::Vector2i placementSpot;

	void generateLayer(std::string line);

	void placeEmpty();

	void placeWall();

	void placeBoss();
	
};

