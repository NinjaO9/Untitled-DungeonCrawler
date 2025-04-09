#include "Ray.hpp"

void Ray::displayRay(sf::RenderWindow& window)
{
    window.draw(line);
}

void Ray::rayCast(sf::RectangleShape& obj,sf::RenderWindow& window)
{
    std::vector<Ray*> rays;
    for (int degree = -180; degree < 180; degree++)
    {
        //rays.push_back(new Ray(*this));
        //rays[degree + 180]->updateRay(obj, window);
        //rays[degree + 180]->displayRay(window);
        displayRay(window);
        line[1].position = line[1].position.rotatedBy(sf::Angle(sf::degrees(degree)));
    }
    //std::cout << rays.size() << std::endl;
    //rays.clear();
    //std::cout << rays.size() << std::endl;

}

bool Ray::intersects(sf::RectangleShape& obj, sf::Vector2f& rayCoords)
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

void Ray::setRayCoords()
{
    line[0].position = sf::Vector2f(sf::Mouse::getPosition());
    line[0].color = sf::Color::Red;
    line[1].position = sf::Vector2f(100, 100);
    line[1].color = sf::Color::White;
}

void Ray::updateRay(sf::RectangleShape& obj, sf::RenderWindow& window)
{
    float deltaX = 0, deltaY = 0;
    line[0].position = (sf::Vector2f)sf::Mouse::getPosition(window);
    sf::Vector2f origin = line[0].position;
    for (;hypotf(deltaX, deltaY) < maxDistance; deltaX++, deltaY++)
    {
        line[1].position = sf::Vector2f(origin.x + deltaX, origin.y + deltaY);
        if (intersects(obj, line[1].position))
        {
            break;
        }
    }
}
