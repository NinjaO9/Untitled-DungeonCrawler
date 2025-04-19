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
		this->Sprite = (new sf::Sprite(TextureManager::getInstance()->getTexture("Temp"))); // temp image (obv)'
		initGameManager();
	}
	// destructor
	~Weapon()
	{

	}

	virtual int calcdmg(const int& WDamage);

	int getdmg();
	void setdmg(const int& WDamage);

	void BaseWeaponATK(const int& WDamage);

	void initGameManager();

private:
	// enter vars here
	int dmg;

	sf::Sprite* Sprite;
	GameManager* gm;

};

