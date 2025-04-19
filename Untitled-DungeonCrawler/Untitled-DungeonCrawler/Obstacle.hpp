#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"

class Obstacle : public GameObject
{
public:
	// enter funcs here
	Obstacle(sf::Vector2f pos);
	
	sf::Sprite& getModel() { return *this->sprite; }

private:
	sf::Sprite* sprite;
	// enter vars here
};

