#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
class RayCast
{
public:

	RayCast(float maxDistance = 100 /* How far the ray can go before sight is cut off*/, float fov = 60 /* field of view */, int rayCount = 20 /* Count of rays - more rays = more precision, but also more taxing on system*/)
	{
		line = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->maxDistance = maxDistance;
		this->rayCount = rayCount;
		this->fov = fov;
		this->angleStep = (fov/rayCount); // determine how far apart the rays should be from each other
		this->startAngle = -(fov/2); // when raycasting, the cast will sweep from startAngle -> fov
		this->rayDir = sf::Vector2f(1, 1);
	}

	~RayCast()
	{
		std::cout << "DELETING RAY" << std::endl;
	}

	void displayRay(sf::RenderWindow& window);

	void rayCast(std::vector<sf::Sprite>& obj, sf::RenderWindow& window, sf::Vector2f origin);

	bool intersects(sf::Sprite& obj, sf::Vector2f& rayCoords);

	void setRayCoords();

	void setDirection(sf::Vector2f& dir);

	void setOrigin(sf::RectangleShape& originSpot);

	sf::Vector2f& getDirection();

	sf::VertexArray& getRayCoords();

	void updateRay(std::vector<sf::Sprite>& obj, sf::RenderWindow& window, sf::Vector2f origin);

private:

	sf::VertexArray line;
	sf::Vector2f rayDir;
	float maxDistance;
	int rayCount;
	float angleStep;
	float fov;
	float startAngle;
	
};