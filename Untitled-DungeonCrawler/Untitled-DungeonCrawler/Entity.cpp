#include "Entity.hpp"

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