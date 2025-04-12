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

	Enemy(int hp = 0, float viewDistance = 50, float attackDistance = 5, float idleTimer = 10, sf::Vector2f pos = sf::Vector2f(0,0)) 
		: Entity(hp, pos, "Enemy")
	{
		this->state = IDLE;
		this->viewDistance = viewDistance;
		this->attackDistance = attackDistance;
		this->idleTimer = idleTimer;
		this->defaultTime = idleTimer;
		this->atTarget = false;
		this->targetPos = sf::Vector2f(200,200);
		this->getModel().setSize(sf::Vector2f(32, 32)); // ALSO TEMPORARY
		this->getModel().setFillColor(sf::Color::Red); // TEMPORARY - DELTE WHEN RECTANGLESHAPE IS CHANGED TO SPRITE
		this->getModel().setPosition(pos);
	}

	void update() override;

private:

	State state;
	sf::Vector2f targetPos; // used to determine where the enemy wants to walk to

	int defaultTime; // default time for the idleTimer to be at

	float viewDistance;
	float attackDistance;
	float idleTimer; // possible value to use when allowing the enemy in a idle state

	bool atTarget;

	State updateState();

	bool canSeePlayer();

	bool playerInRange();

	void runIdle();

	void runPatrol();

	void runChase();

	void runAttack();

	void getNewTargetPos();

};

