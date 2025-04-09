#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
class Ray
{
public:

	Ray(float maxDistance)
	{
		line = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->maxDistance = maxDistance;
	}

	Ray(Ray& const oldRay)
	{
		//std::cout << "MAKING NEW RAY FROM RAY" << std::endl;
		this->line = oldRay.line;
		this->maxDistance = oldRay.maxDistance;
	}

	~Ray()
	{
		std::cout << "DELETING RAY" << std::endl;
	}

	void displayRay(sf::RenderWindow& window);

	void rayCast(sf::RectangleShape& obj, sf::RenderWindow& window);

	bool intersects(sf::RectangleShape& obj, sf::Vector2f& rayCoords);

	void setRayCoords();

	void updateRay(sf::RectangleShape& obj, sf::RenderWindow& window);

private:

	sf::VertexArray line;
	float maxDistance;
	
};