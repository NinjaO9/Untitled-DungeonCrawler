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

	if (WDamage == 0)
	{
		//no damage is delt
		TotalDMG = 0;
	}
	else
	{
		//calculates damage based on multiplyers and level 
		TotalDMG = WDamage + (sword.getLVLMult() * gm->getPlayer()->getLevel());
	}
	return TotalDMG;
}

int Weapon::getdmg()
{
	return dmg;
}

void Weapon::setdmg(const int& WDamage)
{
	//passes Damage in to get calculated
	dmg = calcdmg(WDamage);
}

void Weapon::BaseWeaponATK(const int& WDamage)
{


	Entity test(defaultStatLine, defaultGrowths, 1, (sf::Vector2f)sf::Mouse::getPosition(*(gm->getWindow())));

	//attacking upward
	if (gm->getPlayer()->getDirection() == sf::Vector2i{0,-1}) 
	{
		//sets sprite to upward slash
		sf::Sprite* upSprite = new sf::Sprite(TextureManager::getInstance()->getTexture("up"));
		test.setModel(upSprite); 
		sf::FloatRect up = test.getModel().getLocalBounds();
		test.getModel().setOrigin(sf::Vector2f(up.size.x / 2, up.size.y / 2));
		test.getModel().setScale(sf::Vector2f(1, 1));
		test.getModel().setPosition(gm->getPlayerPos() + sf::Vector2f(gm->getPlayer()->getDirection() * 30));
	}
	//attacking downward
	if (gm->getPlayer()->getDirection() == sf::Vector2i{ 0,1 })
	{
		//sets sprite to downward slash
		sf::Sprite* downSprite = new sf::Sprite(TextureManager::getInstance()->getTexture("down")); 
		test.setModel(downSprite);
		sf::FloatRect down = test.getModel().getLocalBounds();
		test.getModel().setOrigin(sf::Vector2f(down.size.x / 2, down.size.y / 2));
		test.getModel().setScale(sf::Vector2f(1, 1));
		test.getModel().setPosition(gm->getPlayerPos() + sf::Vector2f(gm->getPlayer()->getDirection() * 30));
	}
	//attacking left
	if (gm->getPlayer()->getDirection() == sf::Vector2i{ -1,0 })
	{
		//sets sprite to left slash
		sf::Sprite* leftSprite = new sf::Sprite(TextureManager::getInstance()->getTexture("left"));
		test.setModel(leftSprite);
		sf::FloatRect left = test.getModel().getLocalBounds();
		test.getModel().setOrigin(sf::Vector2f(left.size.x / 2, left.size.y / 2));
		test.getModel().setScale(sf::Vector2f(1, 1));
		test.getModel().setPosition(gm->getPlayerPos() + sf::Vector2f(gm->getPlayer()->getDirection() * 30));
	}
	//attacking right
	if (gm->getPlayer()->getDirection() == sf::Vector2i{ 1,0 })
	{
		//sets sprite to right slash
		sf::Sprite* rightSprite = new sf::Sprite(TextureManager::getInstance()->getTexture("right"));
		test.setModel(rightSprite);
		sf::FloatRect right = test.getModel().getLocalBounds();
		test.getModel().setOrigin(sf::Vector2f(right.size.x / 2, right.size.y / 2));
		test.getModel().setScale(sf::Vector2f(1, 1));
		test.getModel().setPosition(gm->getPlayerPos() + sf::Vector2f(gm->getPlayer()->getDirection() * 30));
	}
	//attacks using last used attack direction
	else
	{
		test.getModel().setScale(sf::Vector2f(1, 1));
		test.getModel().setPosition(gm->getPlayerPos() + sf::Vector2f(gm->getPlayer()->getDirection() * 30));
	}

	//draws the test model, baseed on directing above
	gm->getWindow()->draw(test.getModel());  

	gm->getWindow()->display();  
	vector<Entity*> killedEntities;

	//checks all enemies
	for (auto* enemy : gm->getEnemies()) 
	{

		if (test.getModel().getGlobalBounds().findIntersection(enemy->getModel().getGlobalBounds()))//intersection
		{
			setdmg(WDamage); //sets damage to weapon damage + multiplier
			bool killed = enemy->handleDamage(getdmg());
			if (killed)
			{
				killedEntities.push_back(enemy);
			}
			cout << "hit! for: " << getdmg() << endl;
		}
		else // if nothing is hit, no damage is delt
		{
			setdmg(0);
		}
	}
	for (auto* dead : killedEntities)
	{
		auto index = std::find(gm->getEnemies().begin(), gm->getEnemies().end(), dead);
		gm->getEnemies().erase(index);


		delete dead;
	}
	cout << "ENEMY COUNT ON LEVEL: " << gm->getEnemies().size() << endl;
	//cout << "Killed: " << killedEntities.size() << " in one swing!" << endl;
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