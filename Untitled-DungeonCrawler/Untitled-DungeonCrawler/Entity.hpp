#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Stats.hpp"

class Entity : public GameObject
{
public:

	Entity(Stats stats=defaultStatLine, Growths grows=defaultGrowths, int lvl = 1, sf::Vector2f pos = sf::Vector2f(0, 0), string tag = "Missing-Tag")
		: GameObject(pos, tag)
	{
		statLine = stats;
		statLine.setGrowths(grows);
		level = lvl;

	}

	sf::Sprite& getModel() { return *this->model; } 
	void setModel(sf::Sprite* const newSprite) { this->model = newSprite; }
	void setLevel(int newlevel) { this->level = newlevel; }
	int getLevel() { return level; }
	Stats& getStats() { return statLine; }

	

	virtual void levelUp();

	virtual ~Entity();

private:
	int level;
	Stats statLine;
	sf::Sprite* model;

};

