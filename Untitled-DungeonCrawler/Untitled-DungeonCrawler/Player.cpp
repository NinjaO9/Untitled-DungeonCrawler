#include "Player.hpp"

void Player::update() {
	sf::Vector2f pos = GameObject::getPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { pos.y -= getStats().getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) { pos.x -= getStats().getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { pos.y += getStats().getSpeed(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) { pos.x += getStats().getSpeed(); }
		GameObject::setPos(pos);
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
