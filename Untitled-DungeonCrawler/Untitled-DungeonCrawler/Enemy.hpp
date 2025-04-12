#pragma once
#include "Entity.hpp"

enum State
{
	IDLE,
	PATROL,
	CHASE,
	ATTACK
};

class Enemy : public Entity
{
public:

	Enemy(int hp = 0) 
		: Entity(hp, sf::Vector2f(0, 0), "Enemy")
	{
		state = IDLE;
	}

	void update() override;

	State updateState();

	bool canSeePlayer();

private:

	State state;
	sf::Vector2f targetPos; // used to determine where the enemy wants to walk to
	float viewDistance;
	float attackDistance;

	float patrolTimer; // possible value to use when allowing the enemy in a patrol state

	bool playerInRange();

	void runIdle();

	void runPatrol();

	void runChase();

	void runAttack();

};

