#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"

class Entity : public GameObject
{
public:

	Entity(int hp = 10, float spd = 0.5, int atk = 1, int def = 0, int grow[5] = nullptr, int lvl = 1, sf::Vector2f pos = sf::Vector2f(0, 0), string tag = "Missing-Tag")
		: GameObject(pos, tag)
	{
		this->maxHp = hp;
		this->curHp = maxHp;
		this->speed = spd;
		this->attack = atk;
		this->defense = def;
		
		
		
	}

	sf::Sprite& getModel() { return *this->model; } 

	void setModel(sf::Sprite* const newSprite) { this->model = newSprite; }
	void setMaxHp(int newhp) { curHp += newhp-maxHp; maxHp = newhp; }
	void setCurHp(int newhp) { curHp = newhp; }
	void setSpeed(float newspd) { speed = newspd; }
	void setAttack(int newatk) { attack = newatk; }
	void setDefense(int newdef) { defense = newdef; }
	void setLevel(int newlevel) { level = newlevel; }
	void setGrowths(int newhpg, int newspdg, int newatkg, int newdefg) {
		growths[0] = newhpg;
		growths[1] = newspdg;
		growths[2] = newatkg;
		growths[3] = newdefg;
	}
	void setGrowths(int newhpg, int newspdg, int newatkg, int newdefg, int newspg) {
		growths[0] = newhpg;
		growths[1] = newspdg;
		growths[2] = newatkg;
		growths[3] = newdefg;
		growths[4] = newspg;
	}
	int getMaxHp() { return maxHp; }
	int getCurHp() { return curHp; }
	float getSpeed() { return speed; }
	int getAttack() { return attack; }
	int getDefense() { return defense; }
	int getLevel() { return level; }
	int getGrowths(int n) {
		return growths[n];
	}

	virtual void levelUp();

	virtual ~Entity();

private:

	int maxHp;
	int curHp;
	float speed;
	int attack;
	int defense;
	int level;
	
	//growths
	int growths[5]; //this is an array of values between 0-100, in order of HP,SPD,ATK,and DEF

	sf::Sprite* model;

};

