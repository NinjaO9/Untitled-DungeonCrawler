#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"

class Entity : public GameObject
{
public:

	Entity(int maxHp=0, sf::Vector2f pos = sf::Vector2f(0,0), string tag = "Missing-Tag")
		: GameObject(pos, tag)
	{
		this->maxHp = maxHp;
		this->speed = 0.09;
		this->model = nullptr; // get rid of warnings
	}

	sf::Sprite& getModel() { return *this->model; } 

	void setModel(sf::Sprite* const newSprite) { this->model = newSprite; }

	float getSpeed() const;

	virtual ~Entity();

private:

	int maxHp;
	float speed;
	sf::Sprite* model;

};

