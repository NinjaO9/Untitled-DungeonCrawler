#include "Entity.hpp"

Entity::~Entity()
{
    delete model;
}

void Entity::levelUp() {
	setLevel(getLevel() + 1);
	for (int i = 0;i < 5; i++) {
		if (rand() % 100 <= getGrowths(0)) {
			setMaxHp(getMaxHp() + 1);
		}
		if (rand() % 100 <= getGrowths(1)) {
			setSpeed(getSpeed() + 0.1);
		}
		if (rand() % 100 <= getGrowths(2)) {
			setAttack(getAttack() + 1);
		}
		if (rand() % 100 <= getGrowths(3)) {
			setDefense(getDefense() + 1);
		}
	}
}