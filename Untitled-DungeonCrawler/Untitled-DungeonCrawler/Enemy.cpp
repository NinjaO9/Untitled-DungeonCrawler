#include "Enemy.hpp"

void Enemy::update()
{
	setPos(this->getModel().getPosition());
	switch (state)
	{
	case IDLE:
		runIdle();
		cout << "IDLE " << idleTimer <<endl;
		break;
	case PATROL:
		runPatrol();
		cout << "PATROL" << endl;
		break;
	case CHASE:
		runChase();
		cout << "CHASE" << endl;
		break;
	case ATTACK:
		runAttack();
		cout << "ATTACK" << endl;
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
	if (idleTimer <= 0)
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
	idleTimer--;
}

void Enemy::runPatrol()
{
	// patrol/walk animation
	float distance = checkDistance(this->targetPos);
	if (distance == 0) { getNewTargetPos(); idleTimer += defaultTime; return; } // prevent divide by 0 error; give the enemy some more time to rest before patrolling to a new spot
	sf::Vector2f direction(((targetPos.x - getPos().x)/ distance), ((targetPos.y - getPos().y)/ distance)); // Normalized(?) vector to tell the direction of where the enemy needs to go

	this->getModel().move(direction * getSpeed()); // moving the enemy however much in a certain direction

	if (checkDistance(this->targetPos) <= getSpeed()) // 'close enough' (speed can cause the enemy to overshoot their target, so we will give them an error margin of speed)
	{
		idleTimer += defaultTime;
		getNewTargetPos();
	}
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

void Enemy::getNewTargetPos() // Super Janky code, but a proof of concept
{ 
	// This code needs to be revised to check if the enemy can actually make it to a given location in a straight line. If not, then a new position needs to be rolled
	// Chances are, you will have to check within the circumfrence of the enemy's view distance and find a valid position inside of there.
	int rNum = rand(), yDir = 0, xDir = 0;
	switch (rNum % 2)
	{
	case 0:
		yDir = -1;
		break;
	case 1:
		yDir = 1;
		break;
	}
	rNum = rand();
	switch (rNum % 2)
	{
	case 0:
		xDir = -1;
		break;
	case 1:
		xDir = 1;
		break;
	default:
		break;
	}
	rNum = rand() % (int)viewDistance;
	sf::Vector2f direction(xDir, yDir);
	targetPos = this->getPos() + (direction * (float)rNum);
}
