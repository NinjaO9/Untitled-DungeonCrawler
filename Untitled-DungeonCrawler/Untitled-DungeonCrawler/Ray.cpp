#include "Ray.hpp"

void RayCast::displayRay(sf::RenderWindow& window)
{
    window.draw(line);
}

void RayCast::rayCast(sf::RectangleShape& obj,sf::RenderWindow& window, sf::Vector2f origin)
{
    
    for (float i = 0; i < rayCount; i++) // generate rays
    {
        float angleDeg = (startAngle + (angleStep * i)); // get new degree
        float angleRad = (angleDeg * 3.14159) / 180; // convert degree to radians
        std::cout << "Degree: " << angleDeg << " Radians: " << angleRad << std::endl;
        rayDir = sf::Vector2f(std::cos(angleRad), std::sin(angleRad)); // normalize
        updateRay(obj, window, origin); //update new ray
        displayRay(window);
    }
}

bool RayCast::intersects(sf::RectangleShape& obj, sf::Vector2f& rayCoords)
{
    sf::FloatRect point(rayCoords, sf::Vector2f(1, 1));
    if (obj.getGlobalBounds().findIntersection(point))
    {
        //std::cout << "INTERSECTION!!!" << std::endl;
        return true;
    }
    //std::cout << " NO INTERSECTION!!!" << std::endl;
	return false;
}

void RayCast::setRayCoords()
{
    line[0].position = sf::Vector2f(sf::Mouse::getPosition());
    line[0].color = sf::Color::Red;
    line[1].position = sf::Vector2f(100, 100);
    line[1].color = sf::Color::White;
}

void RayCast::setDirection(sf::Vector2f& dir)
{
    this->rayDir = dir;
}

void RayCast::setOrigin(sf::RectangleShape& originSpot)
{
    this->line[0].position = originSpot.getPosition();
}

sf::Vector2f& RayCast::getDirection()
{
    return rayDir;
}

sf::VertexArray& RayCast::getRayCoords()
{
    return line;
}

void RayCast::updateRay(sf::RectangleShape& obj, sf::RenderWindow& window, sf::Vector2f origin)
{
    float deltaX = 0, deltaY = 0, delta = std::hypotf(deltaX,deltaY);
    //line[0].position = (sf::Vector2f)sf::Mouse::getPosition(window);
    line[0].position = origin;
    sf::Vector2f hitPoint = line[0].position; // start the hit from the beginning of the ray (mouse)

    for (;delta < maxDistance; deltaX++, deltaY++)
    {
        delta = std::hypotf(deltaX, deltaY);
        line[1].position = hitPoint + (rayDir * delta); // determine distance multiplied by the direction
        if (intersects(obj, line[1].position))
        {
            break;
        }
    }
}
