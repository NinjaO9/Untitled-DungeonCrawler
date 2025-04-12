#include "GameObject.hpp"

GameObject::~GameObject(){} // Nothing happens, each game object should have its own way of deleting

void GameObject::update(){} // Nothing happens, each game object should have its own way of updating

float GameObject::checkDistance(sf::Vector2f& const origin, sf::Vector2f& const target)
{
    return sqrt(powf(target.x - origin.x, 2) + powf(target.y - origin.y, 2));
}

float GameObject::checkDistance(sf::Vector2f& const target)
{
    return sqrt(powf(target.x - this->pos.x, 2) + powf(target.y - this->pos.y, 2));
}