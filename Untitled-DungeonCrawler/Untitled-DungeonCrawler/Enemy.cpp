#include "Enemy.hpp"

void Enemy::update()
{
	std::cout << "I am updating!" << std::endl;
	setPos(this->getModel().getPosition());
	switch (state)
	{
	case IDLE:
		runIdle();
		break;
	case PATROL:
		runPatrol();
		break;
	case CHASE:
		runChase();
		break;
	case ATTACK:
		runAttack();
		break;
	default:
		break;
	}
	state = updateState();

}

State Enemy::updateState()
{
	sf::Vector2f TEMP(0, 0); // DELTE ME AFTER GETTING PLAYER POSITION
	if (canSeePlayer())
	{
		if (checkDistance(TEMP /* TEMP IS A TEMPORARY VARIABLE. THIS SHOULD BE REPLACED WITH PLAYER POSITION */) < attackDistance)
		{
			return ATTACK; // If the enemy can see the player and is close enough to land an attack, try to attack
		}
		return CHASE; // If the enemy can see the player, but is too far from the player, chase the player down
	}
	if (patrolTimer > 0)
	{
		return PATROL; // Patrol the area where the enemy is if there is time to patrol
	}
	return IDLE; // Otherwise, idle for some time

}

bool Enemy::canSeePlayer()
{
	if (!playerInRange()) { return false; }
	return true; // work on making a function to see if the player can be seen by the enemy
}

bool Enemy::playerInRange()
{
	return false; // gotta come back to work on this function eventually
}

void Enemy::runIdle()
{
	// idle animation
}

void Enemy::runPatrol()
{
	// patrol/walk animation
	// patrol code
}

void Enemy::runChase()
{
	// chase animation
	// chase code
}

void Enemy::runAttack()
{
	// attack animation
	// attack code
}
