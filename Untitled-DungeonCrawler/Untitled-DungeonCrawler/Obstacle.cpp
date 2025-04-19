#include "Obstacle.hpp"

Obstacle::Obstacle(sf::Vector2f pos)
{
	sprite = new sf::Sprite(TextureManager::getInstance()->getTexture("Rock"));
	sprite->setPosition(pos);
}