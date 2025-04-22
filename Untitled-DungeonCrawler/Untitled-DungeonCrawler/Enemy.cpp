#include "Enemy.hpp"
#include "GameManager.hpp"
#include "LevelManager.hpp"
#define PI 3.14159

void Enemy::update()
{
	setPos(this->getModel().getPosition());
	PlayerRay[0].position = getPos();
	PatrolRay[0].position = getPos();
	prevState = state;
	switch (state)
	{
	case IDLE:
		runIdle();
		//cout << "IDLE " << idleTimer <<endl;
		break;
	case PATROL:
		runPatrol();
		//cout << "PATROL" << endl;
		break;
	case CHASE:
		runChase();
		//cout << "CHASE" << endl;
		break;
	case ATTACK:
		runAttack();
		cout << "ATTACK" << endl;
		break;
	default:
		break;
	}
	PlayerRay[1].position = gm->getMousePos();
	PatrolRay[1].position = targetPos;
	state = updateState();
}

sf::VertexArray Enemy::getPatrolRay() const
{
	return PatrolRay;
}

sf::VertexArray Enemy::getPlayerRay() const
{
	return PlayerRay;
}

State Enemy::updateState()
{
	if (canSeePlayer())
	{
		PlayerRay[1].color = sf::Color::Green; // visually show that the player is seen by the enemy
		if (checkDistance(gm->getMousePos() /* THIS IS A TEMPORARY VARIABLE. THIS SHOULD BE REPLACED WITH PLAYER POSITION */) < attackDistance)
		{
			return ATTACK; // If the enemy can see the player and is close enough to land an attack, try to attack
		}
		return CHASE; // If the enemy can see the player, but is too far from the player, chase the player down
	}
	PlayerRay[1].color = sf::Color::Red; // visually show that the player is NOT seen by the enemy
	if (prevState == CHASE) { getNewTargetPos(); } // make the enemy get a new position if they lose sight of the player
	if (idleTimer <= 0)
	{
		return PATROL; // Patrol the area where the enemy is if there is time to patrol
	}
	return IDLE; // Otherwise, idle for some time

}

bool Enemy::canSeePlayer()
{
	if (!playerInRange()) {return false; } // if the player is not in range, there is no need to check for anything else
	if (!isInFOV()) { return false; } // if the enemy is already chasing the player, FOV doesn't matter
	
	return isTargetPosValid(gm->getMousePos()); // If everything else passes, the enemy should be able to see the player in a direct line of sight (replace 'true' with playerSeen)
}

bool Enemy::playerInRange()
{
	return checkDistance(gm->getMousePos()) < viewDistance; 
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
		idleTimer = defaultTime;
		handleCollision();
		getNewTargetPos();
	}
	updateDirection();
}

void Enemy::runChase()
{
	// chase animation
	// chase code

	targetPos = gm->getMousePos(); // change code eventually
	runPatrol();
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
	int rNum = rand() % 2, yDir = rand(), xDir = rand();
	int attempt = 0;
	bool isValid = false;
	while (!isValid && attempt != 5) // only allow the enemy to try getting a new target 5 times before giving up
	{
		switch (rNum)
		{
		case 0:
			yDir *= -1;
			break;
		default:
			yDir *= 1;
		}
		rNum = rand() % 2;
		switch (rNum)
		{
		case 0:
			xDir *= -1;
			break;
		default:
			xDir *= 1;
		}
		rNum = rand() % (int)viewDistance;
		sf::Vector2f direction(xDir, yDir);
		targetPos = this->getPos() + (direction.normalized() * (float)rNum);
		isValid = isTargetPosValid(targetPos);
		attempt++;
	}
	if (attempt == 5)
	{
		targetPos = this->getModel().getPosition();
		//std::cout << "I give up!" << std::endl;
	}

}

bool Enemy::isInFOV()
{
	float degree = getDegreeTo(gm->getMousePos());
	//std::cout << degree << std::endl;
	return degree < (float)fov/2;
}

float Enemy::getDegreeTo(sf::Vector2f& const target) // This function took me way too long dude
{
	sf::Vector2f dirToTarget = target - getPos();
	float angle = atan2f(dirToTarget.y, dirToTarget.x) - atan2f(directon.y, directon.x); // get the angle difference in radians from [-pi, pi]
	angle *= 180 / PI; // convert raidans to degrees

	return abs(angle); // abs value to ensure equal evaluation
}

void Enemy::updateDirection()
{
	if (state == IDLE) { return; } // if the enemy is idle, they can stay looking in the direction they are already looking at
	sf::Vector2f distanceVector = targetPos - this->getPos();
	if (distanceVector.x == 0)
	{
		if (distanceVector.y == 0) { directon = sf::Vector2f(0, 0); }
		else { directon = sf::Vector2f(0, 1); /* Janky solution */ }
	}
	else if (distanceVector.y == 0)
	{
		if (distanceVector.x == 0) { directon == sf::Vector2f(0, 0); }
		else { directon = sf::Vector2f(1, 0); }
	}
	else
	{
		directon = sf::Vector2f(distanceVector.normalized().x, distanceVector.normalized().y); // converting difference to the unit vector coords
	}

//	std::cout << "DIRECTION X: " << directon.x << " DIRECTION Y: " << directon.y << std::endl;
}

bool Enemy::isTargetPosValid(sf::Vector2f target)
{
	float distance = checkDistance(target);
	bool isValid = true;
	//sf::Vector2f tempPos = getPos();
	sf::Vector2f direction(((target.x - getPos().x) / distance), ((target.y - getPos().y) / distance));
	sf::RectangleShape testRect({ 32,32 });
	//sf::FloatRect simulationRect(tempPos, sf::Vector2f(32, 32));
	testRect.setOrigin({ testRect.getPosition().x / 2, testRect.getPosition().y / 2 });
	//testRect.setPosition(tempPos);
	

	sf::Sprite tempSprite = this->getModel();
	sf::Vector2f tempPos = tempSprite.getPosition();

	for (int i = 1; checkDistance(tempPos, target) > 1; i++) // possibly change i++ to i += 32; this is because we are doing a 32x32 sprite style, so this could be helpful to prevent a higher number of operations
	{
		tempSprite.move(direction);
		tempPos = tempSprite.getPosition();
		//testRect.setPosition(tempPos);
		for (Obstacle* wall : gm->getLevel()->getTiles()) // replace with a literal wall class eventually
		{
			//cout << "CHECK WALL" << endl;
			if (tempSprite.getGlobalBounds().findIntersection(wall->getModel().getGlobalBounds()))
			{
				isValid = false;
				//cout << "COLLISION!" << endl;
				break;
			}
			PlayerRay[1].position = tempPos;

		}
		if (!isValid) { /*cout << "INVALID" << endl;*/ break; }
		//std::cout << "loop" << std::endl;
	}
	//std::cout << isValid << std::endl;
	return isValid;
}

void Enemy::handleCollision()
{
	for (Obstacle* wall : gm->getLevel()->getTiles())
	{
		auto intersection = this->getModel().getGlobalBounds().findIntersection(wall->getModel().getGlobalBounds());
		if (intersection.has_value())
		{
			sf::Vector2f trueIntersection(this->getModel().getPosition().x - intersection.value().position.x, this->getModel().getPosition().y - intersection.value().position.y);
			int ySign = 0, xSign = 0;
			if (trueIntersection.x == this->getModel().getPosition().x) { xSign = 0; }
			else if (trueIntersection.x > 0) { xSign = 1; }
			else { xSign = -1; }
			if (trueIntersection.y == this->getModel().getPosition().y) { ySign = 0; }
			else if (trueIntersection.x > 0) { ySign = -1; }
			else { ySign = 1; }
			this->getModel().move({intersection.value().size.x * xSign + (2 * xSign), -intersection.value().size.y * ySign + (2 * ySign)});
			break;
		}
	}
}
