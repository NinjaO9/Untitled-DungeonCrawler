#include "Entity.hpp"
#include "GameManager.hpp"

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
    cout << "Enemy has: " << this->hp << " health remaining!" << endl;
    if (this->hp == 0)
    {
        if (this->getTag() == "Enemy")
        {
            auto index = std::find(gm->getEnemies().begin(), gm->getEnemies().end(), dynamic_cast<Enemy*>(this));
            gm->getEnemies().erase(index);
            cout << "ENEMY COUNT ON LEVEL: " << gm->getEnemies().size() << endl;
        }
        else // there should only ever be an enemy or player as an entity. If we add more thats an issue for later us (this is being written on Tuesday 4/22/25, so)
        {
            // kill player
        }
        delete this;
    }
}

Entity::~Entity()
{
    delete model;
}
