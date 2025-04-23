#pragma once
#include "GameObject.hpp"
#include "Entity.hpp"  
#include "TextureManager.hpp"
class GameManager;

class Weapon : public GameObject
{
public:
	// enter funcs here (gets numbers from other classes/ base functions)

	
	// constructor
	Weapon(int dmg = 0)
	{
		this->upSprite = (new sf::Sprite(TextureManager::getInstance()->getTexture("up"))); // upwards slash
		this->downSprite = (new sf::Sprite(TextureManager::getInstance()->getTexture("down"))); // downwards slash
		this->leftSprite = (new sf::Sprite(TextureManager::getInstance()->getTexture("left"))); // left slash
		this->rightSprite = (new sf::Sprite(TextureManager::getInstance()->getTexture("right"))); // right slash
		initGameManager();
	}
	// destructor
	~Weapon()
	{

	}
	
	//calculates damage
	virtual int calcdmg(const int& WDamage);

	//gets damage
	int getdmg();
	//sets damage
	void setdmg(const int& WDamage);
	//function for weapon attacks
	void BaseWeaponATK(const int& WDamage);

	void initGameManager();

private:
	// enter vars here
	int dmg;

	sf::Sprite* upSprite;
	sf::Sprite* leftSprite;
	sf::Sprite* rightSprite;
	sf::Sprite* downSprite;
	GameManager* gm;

};

//specific class for sword
class Sword : public Weapon
{
public:
	//constructor
	Sword(int BaseDMG = 5, int LVLMult = 0.25)
	{

	}
	//destructor
	~Sword()
	{

	}
	//getter
	int getBaseDMG();
	//getter
	double getLVLMult();

private:
	//varibles
	int BaseDMG = 5;
	double LVLMult = 0.25;
};