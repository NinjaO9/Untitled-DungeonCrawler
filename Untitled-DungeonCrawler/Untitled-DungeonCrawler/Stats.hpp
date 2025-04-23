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