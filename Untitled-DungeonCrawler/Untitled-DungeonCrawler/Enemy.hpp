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

	Enemy(int hp = 10, float spd = 0.7, int atk = 1, int def = 0, int grow[5] = nullptr, int lvl=1, sf::Vector2f pos = sf::Vector2f(0, 0), float viewDistance /* In pixels */ = 200, float attackDistance/* In pixels */ = 5, float idleTimer/* Time in seconds*/ = 2)
		: Entity(hp,spd,atk,def,grow,lvl,pos,"Enemy")
	{
		
		this->PlayerRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->PatrolRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->state = IDLE;
		this->viewDistance = viewDistance;
		this->attackDistance = attackDistance;
		this->idleTimer = idleTimer * 1000;
		this->defaultTime = idleTimer * 1000;
		this->atTarget = false;
		this->targetPos = sf::Vector2f(101, 101);
		updateDirection();
		this->fov = 60;
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("Temp"))); // temp image (obv)
		sf::FloatRect temp = this->getModel().getLocalBounds();
		this->getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
		this->getModel().setScale(sf::Vector2f(0.032, 0.032)); // Saul Goodman (Temp image) is too massive (like the low-taper fade meme) so I needed to scale it down
		this->getModel().setPosition(pos);
	}

	int getExpReward(){ return this->expReward; }

	void update() override;
	

	sf::VertexArray getPlayerRay() const;
	sf::VertexArray getPatrolRay() const;

private:

	State state, prevState;
	sf::Vector2f targetPos; // used to determine where the enemy wants to walk to
	sf::Vector2f directon;
	sf::VertexArray PlayerRay; // ray to point from this enemy to the player, used for collision detection
	sf::VertexArray PatrolRay; // ray to point from this enemy to the target position

	int defaultTime; // default time for the idleTimer to be at
	int fov;

	float viewDistance;
	float attackDistance;
	float idleTimer; // possible value to use when allowing the enemy in a idle state

	bool atTarget;

	int expReward;

	State updateState();

	bool canSeePlayer();

	bool playerInRange();

	void runIdle();

	void runPatrol();

	void runChase();

	void runAttack();

	void getNewTargetPos();

	bool isInFOV();

	float getDegreeTo(sf::Vector2f& const target);

	void updateDirection();

	bool isTargetPosValid(sf::Vector2f target);

};