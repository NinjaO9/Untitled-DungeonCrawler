#pragma once
#include <algorithm>
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Stats.hpp"

class GameManager;

class Entity : public GameObject
{
public:

	Entity(Stats stats=defaultStatLine, Growths grows=defaultGrowths, int lvl = 1, sf::Vector2f pos = sf::Vector2f(0, 0), string tag = "Missing-Tag")
		: GameObject(pos, tag)
	{
		statLine = stats;
		statLine.setGrowths(grows);
		level = lvl;
		for (int i = 0; i < level;i++) {
			levelUp();
		}
		this->model = nullptr; // get rid of warnings
	}

	sf::Sprite& getModel() { return *this->model; } 
	void setModel(sf::Sprite* const newSprite) { this->model = newSprite; }
	void setLevel(int newlevel) { this->level = newlevel; }
	int getLevel() { return level; }
	Stats& getStats() { return statLine; }

	

	virtual void levelUp();

	void setSpeed(float const speed);

	bool handleDamage(int dmg);

	virtual ~Entity();

private:
	int level;
	Stats statLine;
	sf::Sprite* model;

};

