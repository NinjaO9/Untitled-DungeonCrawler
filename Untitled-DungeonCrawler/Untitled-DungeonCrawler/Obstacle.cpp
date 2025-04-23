#include "Obstacle.hpp"

Obstacle::Obstacle(sf::Vector2f pos)
{
	sprite = new sf::Sprite(TextureManager::getInstance()->getTexture("Wall"));
	sprite->setPosition(pos);
	sprite->setOrigin({ sprite->getPosition().x / 32, sprite->getPosition().y / 32 });
	setPos(pos);
}