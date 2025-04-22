#pragma once
#include "Entity.hpp"
#include "Weapon.hpp"

class Player : public Entity
{
public:
	Player(int hp = 25, float spd = 0.8, int atk = 1, int def = 0, int grow[5] = nullptr, int lvl=1, sf::Vector2f pos = sf::Vector2f(0, 0), int sp = 50)
		: Entity(hp, spd, atk, def, grow, lvl, pos, "Player")
	{
		this->setMaxSp(sp);
		setExpToNext(5 + (getLevel() * 5) * (1 + (getLevel() - 1) / 10));
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("John")));
		this->getModel().setScale(sf::Vector2f(0.032, 0.032));
		this->getModel().setPosition(pos);
		sf::FloatRect temp = this->getModel().getLocalBounds();
		this->getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
	}

	void update() override;

	sf::Vector2f& getPos() override;

	void setPos(sf::Vector2f const newPos) override;

	void levelUp()override;
	void attack(); //should call weapon's attack, this should mostly just be taking in player input
	void checklvlup();

	int getMaxSp() const { return this->maxSp; } 
	int getCurSp() const { return this->curSp; } 
	int getExp() const { return this->exp; }
	int getExpToLvl() const { return this->expToNext; }

	int setMaxSp(int newmaxsp) { curSp += newmaxsp - maxSp; this->maxSp = newmaxsp; } //set max stamina for player, modifies current by the change
	int setCurSp(int newcursp) { this->curSp = newcursp; }
	int setExp(int newexp) { this->exp = newexp; }
	int setExpToNext(int newexptolvl) { this->expToNext = newexptolvl; }

private:
	int maxSp;
	int curSp;
	int exp;
	int expToNext;
	Weapon* equippedWeapon;
};