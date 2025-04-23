#include "Weapon.hpp"
#include "GameManager.hpp"

 
/*
* weapon idea
* 
* NOTE:	weapon and player sprites either need to be connected or just a player with weapon
* maybe a separate attacking sprite, just for weapon hit.
*
* trigger condition, use in main to trigger function call
* 
* if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
* {
* 
* }
*/

int Weapon::calcdmg(const int& WDamage)
{
	Sword sword;
	int TotalDMG = 0;

	TotalDMG = WDamage + (sword.getLVLMult() * 2);// 2 is a placeholder for level

	return TotalDMG;
}

int Weapon::getdmg()
{
	return dmg;
}

void Weapon::setdmg(const int& WDamage)
{
	dmg = calcdmg(WDamage);// any multiplyers
}

void Weapon::BaseWeaponATK(const int& WDamage) 
{
	

	Entity test(defaultStatLine, defaultGrowths, 1, (sf::Vector2f)sf::Mouse::getPosition(*(gm->getWindow())));
	sf::Sprite* tempSprite = new sf::Sprite(TextureManager::getInstance()->getTexture("Temp"));
	test.setModel(tempSprite);
	sf::FloatRect temp = test.getModel().getLocalBounds();
	test.getModel().setOrigin(sf::Vector2f(temp.size.x / 2, temp.size.y / 2));
	test.getModel().setScale(sf::Vector2f(0.01, 0.01));
	test.getModel().setPosition(gm->getMousePos());

	gm->getWindow()->draw(test.getModel());  

	gm->getWindow()->display();  

	for (auto* enemy : gm->getEnemies()) 
	{

		if (test.getModel().getGlobalBounds().findIntersection(enemy->getModel().getGlobalBounds()))//placeholder, but overall intersection
		{
			setdmg(WDamage); 
			enemy->handleDamage(getdmg());
			cout << "hit! for: " << getdmg() << endl;
		}
		else
		{
			setdmg(0);
		}
	}
}

void Weapon::initGameManager()
{
	gm = GameManager::getInstance();
}

//weapon specific functions below (Sword)

int Sword::getBaseDMG()
{
	return BaseDMG;
}

double Sword::getLVLMult()
{
	return LVLMult;
}