#include "Entity.hpp"
#include "GameManager.hpp"

Entity::~Entity()
{
    delete model;
}

void Entity::levelUp() {
	setLevel(getLevel() + 1);
	for (int i = 0;i < 3; i++) {
		if (rand() % 100 <= statLine.getGrowth(0)) {
			statLine.setMaxHp(statLine.getMaxHp() + 1);
		}
		if (rand() % 100 <= statLine.getGrowth(1)) {
			statLine.setSpeed(statLine.getSpeed() + 0.1);
		}
		if (rand() % 100 <= statLine.getGrowth(2)) {
			statLine.setAttack(statLine.getAttack() + 1);
		}
		if (rand() % 100 <= statLine.getGrowth(3)) {
			statLine.setDefense(statLine.getDefense() + 1);
		}
		if (rand() % 100 <= statLine.getGrowth(4)) {
			statLine.setMaxSp(statLine.getMaxSp() + 1);
		}
	}
}
void Entity::handleDamage(int dmg)
{
    getStats().setCurHp(getStats().getCurHp()-dmg);
    cout << "Enemy has: " << getStats().getCurHp() << " health remaining!" << endl;
    if (getStats().getCurHp() == 0)
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
