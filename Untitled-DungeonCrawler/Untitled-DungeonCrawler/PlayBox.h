#pragma once
#include <SFML/Graphics.hpp>
#include "Ray.hpp"
class PlayBox : public sf::RectangleShape
{
public:

	PlayBox(sf::Vector2f direction = sf::Vector2f(0,0))
	{
		vision = RayCast(200);
		rotation = direction;
		vision.setDirection(rotation);
	}

	RayCast& getVision()
	{
		return vision;
	}

	void rotateAll()
	{
		sf::Angle rot(sf::degrees(10));
		this->rotate(rot);
		//vision.setDirection(rotation.rotatedBy(rot));
	}

	void initialize()
	{
		this->setSize(sf::Vector2f(50, 50));
		this->setPosition(sf::Vector2f(250, 250));
		this->setOrigin(sf::Vector2f((this->getSize().x / 2) + this->getPosition().x, (this->getSize().y / 2) + this->getPosition().y));
		this->setFillColor(sf::Color::Yellow);
		vision.setOrigin(*this);
	}

private:

	RayCast vision;
	sf::Vector2f rotation;
};

