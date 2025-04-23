#include "Player.hpp"
using sf::Keyboard::Scancode;

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		handleMovement();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J)) {
		attack();
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
	//if (getStats().getCurSp() > this->equippedWeapon->getSpCost()) { //weapon SP costs will be needed here and then we can check if player's SP is equal to SPcost of weapon
	//	this->equippedWeapon->weaponAttack(); //function for weaponattack needed and will be excecuted here
	//}
}

void Player::checklvlup()
{
	if (getExp() >= getExpToLvl()) {
		Player::levelUp();
	}
}

void Player::handleMovement()
{
	sf::Vector2i direction;
	if (sf::Keyboard::isKeyPressed(Scancode::W))
	{
		direction += {0, -1};
	}
	if (sf::Keyboard::isKeyPressed(Scancode::S))
	{
		direction += {0, 1};
	}
	if (sf::Keyboard::isKeyPressed(Scancode::D))
	{
		direction += {1, 0};
	}
	if (sf::Keyboard::isKeyPressed(Scancode::A))
	{
		direction += {-1, 0};
	}

	this->getModel().move((sf::Vector2f)direction * this->getStats().getSpeed());
}
