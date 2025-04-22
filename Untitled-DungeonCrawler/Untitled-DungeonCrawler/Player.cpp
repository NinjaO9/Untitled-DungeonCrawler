#include "Player.hpp"

void Player::update() {
	sf::Vector2f pos = GameObject::getPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { pos.y -= Entity::getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) { pos.x -= Entity::getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { pos.y += Entity::getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) { pos.x += Entity::getSpeed(); }
		GameObject::setPos(pos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::J)) {
		attack();
	}
}

void Player::levelUp()
{
	setLevel(getLevel()+1);
	exp = exp - expToNext;
	expToNext = 5 + (getLevel() * 5) * (1 + (getLevel() - 1) / 10);
	for (int i = 0;i < 5; i++) {
		if (rand() % 100 <= getGrowths(0)) {
			setMaxHp(getMaxHp() + 1);
		}
		if (rand() % 100 <= getGrowths(1)) {
			setSpeed(getSpeed() + 0.1);
		}
		if (rand() % 100 <= getGrowths(2)) {
			setAttack(getAttack() + 1);
		}
		if (rand() % 100 <= getGrowths(3)) {
			setDefense(getDefense() + 1);
		}
		if (rand() % 100 <= getGrowths(4)) {
			setMaxSp(getMaxSp() + 1);
		}
	}
}

void Player::attack()
{
	if (getCurSp() > this->equippedWeapon->getSpCost()) { //weapon SP costs will be needed here and then we can check if player's SP is equal to SPcost of weapon
		this->equippedWeapon->weaponAttack(); //function for weaponattack needed and will be excecuted here
	}
}

void Player::checklvlup()
{
	if (getExp() >= getExpToLvl()) {
		levelUp();
	}
}
