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

	Enemy(Stats statline=defaultStatLine, Growths grow=defaultGrowths, int lvl = 1, float viewDistance /* In pixels */ = 200, float attackDistance/* In pixels */ = 5, float idleTimer/* Time in seconds*/ = 2, sf::Vector2f pos = sf::Vector2f(0, 0))
		: Entity(statline,grow,lvl,pos,"Enemy")
	{
		
		this->PlayerRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->PatrolRay = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
		this->state = IDLE;
		this->viewDistance = viewDistance;
		this->attackDistance = attackDistance;
		this->idleTimer = idleTimer * 10;
		this->defaultTime = idleTimer * 10;
		this->atTarget = false;
		this->targetPos = pos;
		this->fov = 60;
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("Enemy"))); // temp image (obv)
		sf::FloatRect temp = this->getModel().getLocalBounds();
		this->getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
		updateDirection();


		float scaleX = 32.0f / this->getModel().getTextureRect().size.x;
		float scaleY = 32.0f / this->getModel().getTextureRect().size.y;

		this->getModel().setScale(sf::Vector2f(scaleX, scaleY)); // Saul Goodman (Temp image) is too massive (like the low-taper fade meme) so I needed to scale it down
		this->getModel().setPosition(pos);
		playerPosTimer.start();
	}

	int getExpReward(){ return this->expReward; }

	void update() override;
	

	sf::VertexArray getPlayerRay() const;
	sf::VertexArray getPatrolRay() const;

	sf::Vector2f getDirection() const { return directon; };

	// should only be used for test functions (manipulating where the enemy wants to go)
	sf::Vector2f& getTargetPos() { return targetPos; }

	// should also only be used for test functions (forcing the enemy to check valid positions)
	void checkForcedPos();

	// shouldn't be needed to be called except for test-cases
	void checkCollision() { handleCollision(); }

	bool debugSeesPlayer() { updateDirection(); return canSeePlayer(); }

private:

	State state, prevState;
	sf::Vector2f targetPos; // used to determine where the enemy wants to walk to
	sf::Vector2f directon;
	sf::VertexArray PlayerRay; // ray to point from this enemy to the player, used for collision detection
	sf::VertexArray PatrolRay; // ray to point from this enemy to the target position

	sf::Clock playerPosTimer; // reduce the amount of times the enemy is tracing the player's movement for optimization purposes
	sf::Clock attackCD; // enemy no spam attack, thats bad >:(

	int defaultTime; // default time for the idleTimer to be at
	int fov;

	float viewDistance;
	float attackDistance;
	float idleTimer; // possible value to use when allowing the enemy in a idle state

	bool atTarget;
	bool playerSeen;

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

	void handleCollision();

};