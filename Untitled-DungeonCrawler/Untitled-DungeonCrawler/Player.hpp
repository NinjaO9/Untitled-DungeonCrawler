#pragma once
#include "Entity.hpp"
#include "Weapon.hpp"
#include "Movement.hpp" //needed, unless we make a playermovement class and do most of the work in there as opposed to in player class

class Player : public Entity
{
public:
	Player(int maxHp = 100, int curHp = 100, int maxSP = 50, sf::Vector2f pos = sf::Vector2f(0, 0))
		: Entity(curHp, pos, "Player")
	{
		this->setModel(new sf::Sprite(TextureManager::getInstance()->getTexture("Temp")));//copied these over from enemy cause they're still relevant
		this->getModel().setScale(sf::Vector2f(0.032, 0.032)); 
		this->getModel().setPosition(pos);
	}

	void update() override;

	virtual sf::Vector2f& getPos() override;//well see if these need to be overridden not entirely sure

	virtual void setPos(sf::Vector2f const newPos) override;


	void playermovement(); //if we don't have a playermovement class then itll all be here ig
	void attack(); //should call weapon's attack, this should mostly just be taking in player input

	int getMaxSP() const { return this->maxSP; } //get max stamina for player
	int getCurSP() const { return this->curSP; } //get current stamina for player

private:
	int maxSP;
	int curSP;
	Weapon* equippedWeapon;
}