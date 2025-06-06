#include "GameObject.hpp"
#include "GameManager.hpp"

GameObject::~GameObject(){} // Nothing happens, each game object should have its own way of deleting

void GameObject::update(){} // Nothing happens, each game object should have its own way of updating

sf::Vector2f& GameObject::getPos()
{
    auto ptr = dynamic_cast<Entity*>(this); // is the gameobject an entity?
    if (ptr != nullptr)
    {
        sf::Vector2f mPos = ptr->getModel().getPosition();
        return mPos; // mPos = model position
    }
    return pos;
}

void GameObject::setPos(sf::Vector2f const newPos)
{
    auto ptr = dynamic_cast<Entity*>(this); // is the gameobject an entity?
    if (ptr != nullptr)
    {
    
        ptr->getModel().setPosition(newPos);
    }
    pos = newPos;
}

void GameObject::initializeGameManager()
{
    gm = GameManager::getInstance();
}

float GameObject::checkDistance(sf::Vector2f& const origin, sf::Vector2f& const target)
{
    float distance = sqrt(powf(target.x - origin.x, 2) + powf(target.y - origin.y, 2));
   // std::cout << distance << std::endl;
    return distance;
}

float GameObject::checkDistance(sf::Vector2f& const target)
{
    float distance = sqrt(powf(target.x - this->pos.x, 2) + powf(target.y - this->pos.y, 2));
   /* std::cout << "Target: " << target.x << "," << target.y << " Origin: " << this->pos.x << "," << this->pos.y << std::endl;
    std::cout << "Diff: " << target.x - this->pos.x << "," << target.y - this->pos.y << std::endl;
    std::cout << distance << std::endl;*/
    return distance;

}