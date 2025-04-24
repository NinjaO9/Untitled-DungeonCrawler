#include "Obstacle.hpp"

Obstacle::Obstacle(sf::Vector2f pos)
{
	int texture = rand() % 2;
	switch (texture) // select a random texture to the wall
	{
	case 0:
		sprite = new sf::Sprite(TextureManager::getInstance()->getTexture("Wall1"));
		break;
	case 1:
		sprite = new sf::Sprite(TextureManager::getInstance()->getTexture("Wall2"));
		break;
	default:
		break;
	}
	sprite->setPosition(pos);
	sprite->setOrigin({ sprite->getPosition().x / 32, sprite->getPosition().y / 32 });
	sf::IntRect rect = sprite->getTextureRect();

	sprite->setScale({(32.0f/rect.size.x),(32.0f/rect.size.y)});
	setPos(pos);
}