#include "Player.hpp"

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A || sf::Keyboard::isKeyPressed(sf::Keyboard::S || sf::Keyboard::isKeyPressed(sf::Keyboard::D || sf::Keyboard::isKeyPressed(sf::Keyboard::W) {

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {//same as above
		attack();
	}
}

void Player::attack()
{
	if (getCurSP() > this->equippedWeapon->getSPcost()) { //weapon SP costs will be needed here and then we can check if player's SP is equal to SPcost of weapon
		this->equippedWeapon->weaponAttack(); //function for weaponattack needed and will be excecuted here
	}
}