#include "Entity.hpp"

float Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(float const speed)
{
    this->speed = speed;
}

void Entity::handleDamage(int dmg)
{
    this->hp -= dmg;
    if (this->hp == 0)
    {
        delete this;
    }
}

Entity::~Entity()
{
    delete model;
}
