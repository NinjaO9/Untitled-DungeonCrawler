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

	Enemy(int hp = 0, float viewDistance /* In pixels */ = 200, float attackDistance/* In pixels */ = 5, float idleTimer/* Time in seconds*/ = 2, sf::Vector2f pos = sf::Vector2f(0, 0))
		: Entity(hp, pos, "Enemy")
	{
		this->PlayerRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->PatrolRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->state = IDLE;
		this->viewDistance = viewDistance;
		this->attackDistance = attackDistance;
		this->idleTimer = idleTimer * 1000;
		this->defaultTime = idleTimer * 1000;
		this->atTarget = false;
		this->targetPos = pos;
		this->fov = 60;
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("Temp"))); // temp image (obv)
		sf::FloatRect temp = this->getModel().getLocalBounds();
		this->getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
		//getNewTargetPos();
		updateDirection();



		float scaleX = 32.0f / this->getModel().getTextureRect().size.x;
		float scaleY = 32.0f / this->getModel().getTextureRect().size.y;

		this->getModel().setScale(sf::Vector2f(scaleX, scaleY)); // Saul Goodman (Temp image) is too massive (like the low-taper fade meme) so I needed to scale it down
		this->getModel().setPosition(pos);
	}

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