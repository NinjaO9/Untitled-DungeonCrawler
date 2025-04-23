#pragma once
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "Weapon.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>


class UserInterface {
private:
	int health;
	int stamina;
	int level;
	/*Player* selectedPlayer;
	Weapon *selectedWeapon;
	*/
public:
	UserInterface();
	~UserInterface();
	void update();
	void display();
};
