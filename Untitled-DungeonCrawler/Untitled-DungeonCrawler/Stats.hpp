#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

class Growths {
public:
	Growths(int hpg = 50, int spdg = 10, int atkg = 20, int defg = 10, int spg = 0) {
		hpGrowth = hpg;
		speedGrowth = spdg;
		attackGrowth = atkg;
		defenseGrowth = defg;
		spGrowth = spg;
	}
	Growths(const Growths& copiedGrowths) {
		hpGrowth = copiedGrowths.hpGrowth;
		speedGrowth = copiedGrowths.speedGrowth;
		attackGrowth = copiedGrowths.attackGrowth;
		defenseGrowth = copiedGrowths.defenseGrowth;
		spGrowth = copiedGrowths.spGrowth;
	}
	void setGrowths(int newhpg, int newspdg, int newatkg, int newdefg, int newspg = 0) {

	}

	void setGrowths(const Growths& copiedGrowths) {
		hpGrowth = copiedGrowths.hpGrowth;
		speedGrowth = copiedGrowths.speedGrowth;
		attackGrowth = copiedGrowths.attackGrowth;
		defenseGrowth = copiedGrowths.defenseGrowth;
		spGrowth = copiedGrowths.spGrowth;
	}
	int getHpGrowth() {
		return hpGrowth;
	}
	int getSpeedGrowth() {
		return speedGrowth;
	}
	int getAttackGrowth() {
		return attackGrowth;
	}
	int getDefenseGrowth() {
		return defenseGrowth;
	}
	int getSpGrowth() {
		return spGrowth;
	}
private:
	int hpGrowth;
	int speedGrowth;
	int attackGrowth;
	int defenseGrowth;
	int spGrowth;


};

class Stats {
public:
	Stats(int hp = 10, float spd = 0.7, int atk = 1, int def = 0,int sp = 10) {
		this->maxHp = hp;
		this->curHp = maxHp;
		this->speed = spd;
		this->attack = atk;
		this->defense = def;
		this->maxSp = sp;
		this->curSp = maxSp;
	}
	
	void setMaxHp(int newhp) { curHp += newhp - maxHp; maxHp = newhp; }
	void setCurHp(int newhp) { curHp = newhp; }
	void setSpeed(float newspd) { speed = newspd; }
	void setAttack(int newatk) { attack = newatk; }
	void setDefense(int newdef) { defense = newdef; }
	void setMaxSp(int newmaxsp) { curSp += newmaxsp - maxSp; this->maxSp = newmaxsp; }
	void setCurSp(int newcursp) { this->curSp = newcursp; }
	int getMaxHp() { return maxHp; }
	int getCurHp() { return curHp; }
	float getSpeed() { return speed; }
	int getAttack() { return attack; }
	int getDefense() { return defense; }
	int getMaxSp() const { return maxSp; }
	int getCurSp() const { return curSp; }
	int getGrowth(int n) {
		int growth;
		switch (n) {
		case 0:
			growth = scaling.getHpGrowth();
			break;
		case 1: 
			growth = scaling.getSpeedGrowth();
			break;
		case 2: 
			growth = scaling.getAttackGrowth();
			break;
		case 3: 
			growth = scaling.getDefenseGrowth();
			break;
		case 4: 
			growth = scaling.getSpGrowth();
			break;
		}
		return growth;
	}
	Growths& getGrowths() {
		return scaling;
	}
	void setGrowths(Growths g) { scaling = g; }
private:
	int maxHp;
	int curHp;
	float speed;
	int attack;
	int defense;
	Growths scaling;
	int maxSp;
	int curSp;
};

static Stats defaultStatLine(10 /* hp */, 2 /* spd */, 1 /* atk */, 0 /* def */, 0 /* sp */);
static Growths defaultGrowths(50 /* hpg */, 10 /* spdg */, 20 /* atkg */, 10 /* defg */, 0 /* spg */);

//moved statline and growth tables here so they can be accessed by the create enemy function
#define ENTITY_COUNT 20

Growths inputGrowths[] = { //first value is player, rest are enemies
   Growths(65, 25, 30, 20, 40), //player
   Growths(50, 15, 25, 20, 0),//e1
   Growths(20, 20, 15, 10, 0),//e2...etc
   Growths(35, 10, 30, 15, 0) 
   //goes hp speed attack defense SP
};
Stats inputStats[] = {//first value is player, rest are enemies
Stats(20, 2.0, 1, 1, 30),
Stats(10, 2.0, 2, 2, 0),
Stats(8, 2.3, 3, 0, 0),
Stats(12, 1.7, 1, 1, 0)
//same for stats; random filler, change to more appropriate values
};
Growths growthTable[ENTITY_COUNT];
Stats statTable[ENTITY_COUNT];
int inputCount = std::min((int)(sizeof(inputStats) / sizeof(Stats)), ENTITY_COUNT);