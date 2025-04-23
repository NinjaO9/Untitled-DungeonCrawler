#pragma once
#include "Entity.hpp"
#include "Weapon.hpp"

class Player : public Entity
{
public:
	Player(Stats statline = defaultStatLine, Growths grow = defaultGrowths, int lvl = 1, sf::Vector2f pos = sf::Vector2f(0, 0))
		: Entity(statline, grow, lvl, pos, "Player")
	{
		setExpToNext(5 + (getLevel() * 5) * (1 + (getLevel() - 1) / 10));
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("John")));
		this->getModel().setScale(sf::Vector2f(0.032, 0.032));
		this->getModel().setPosition(pos);
		sf::FloatRect temp = this->getModel().getLocalBounds();
		this->getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
	}

	void update() override;

	void levelUp()override;
	void attack(); //should call weapon's attack, this should mostly just be taking in player input
	void checklvlup();

	int getExp() const { return this->exp; }
	int getExpToLvl() const { return this->expToNext; }
	void setExp(int newexp) { this->exp = newexp; }
	void setExpToNext(int newexptolvl) { this->expToNext = newexptolvl; }

private:
	int exp;
	int expToNext;
	Weapon* equippedWeapon;
	sf::Vector2f direction;
};