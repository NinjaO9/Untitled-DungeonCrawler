#include "Player.hpp"
#include "GameManager.hpp"
#include "LevelManager.hpp"

using sf::Keyboard::Scancode;

void Player::update() {
	sf::Vector2f pos = GameObject::getPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		handleMovement();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J)) {
		attack();
	}
	getStats().setCurSp(getStats().getCurSp() + .05);
	if (getStats().getCurSp() > getStats().getMaxSp()) {
		getStats().setCurSp(getStats().getMaxSp());
	}
}

void Player::levelUp()
{
	exp = exp - expToNext;
	expToNext = 5 + (getLevel() * 5) * (1 + (getLevel() - 1) / 10);
	Entity::levelUp();
}

void Player::attack()
{
//	//if (getStats().getCurSp() > this->equippedWeapon->getSpCost()) { //weapon SP costs will be needed here and then we can check if player's SP is equal to SPcost of weapon
//	//	this->equippedWeapon->weaponAttack(); //function for weaponattack needed and will be excecuted here
//	//}
}

void Player::checklvlup()
{
	if (getExp() >= getExpToLvl()) {
		Player::levelUp();
	}
}

void Player::handleMovement()
{
	sf::Vector2i movement;
	if (sf::Keyboard::isKeyPressed(Scancode::W))
	{
		movement = {0, -1};
		this->direction = { 0,-1 };
	}
	if (sf::Keyboard::isKeyPressed(Scancode::S))
	{
		movement = {0, 1};
		this->direction = { 0,1 };
	}
	if (sf::Keyboard::isKeyPressed(Scancode::D))
	{
		movement = {1, 0};
		this->direction = { 1,0 };
	}
	if (sf::Keyboard::isKeyPressed(Scancode::A))
	{
		movement = {-1, 0};
		this->direction = { -1,0 };
	}

	this->getModel().move((sf::Vector2f)movement * this->getStats().getSpeed());
	handleCollision();
}

sf::Vector2i Player::getDirection()
{
	return direction;
}

void Player::handleCollision()
{
	for (Obstacle* wall : gm->getLevel()->getTiles())
	{
		if (wall == gm->getLevel()->getExitTile()) { 
			break; 
		}

		//if (checkDistance(wall->getPos()) < 10) { continue; }
		//if (wall. == gm->getLevel()->getTiles().end()) { break; }
		if (this->getModel().getGlobalBounds().findIntersection(wall->getModel().getGlobalBounds()))
		{
			this->getModel().move((sf::Vector2f)( -1.0f * ((sf::Vector2f)direction * getStats().getSpeed())));
		}
	}
}
