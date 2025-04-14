#pragma once
#include "GameObject.hpp"

class Entity : public GameObject
{
public:

	Entity(int maxHp=0, sf::Vector2f pos = sf::Vector2f(0,0), string tag = "Missing-Tag")
		: GameObject(pos, tag)
	{
		this->maxHp = maxHp;
		this->speed = 0.09;
	}

	sf::RectangleShape& getModel() { return this->model; } 

	float getSpeed() const;

	virtual ~Entity();

private:

	int maxHp;
	float speed;
	sf::RectangleShape model; // temp; likely will change to sf::Sprite later on

};

