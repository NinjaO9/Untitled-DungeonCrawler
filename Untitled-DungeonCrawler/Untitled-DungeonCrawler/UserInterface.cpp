#include "UserInterface.hpp"
#include <string>
using std::string;

UserInterface::UserInterface() {
	health = 0;
	stamina = 0;
	level = 0;
	//selectedPlayer = nullptr;
}

UserInterface::~UserInterface() {

}

void UserInterface::update() {
	/*health = selectedPlayer->hp;
	* stamina = selectedPlayer->stamina;
	* level = selectedPlayer->level;
	* 
	*/
	health = 99;
	stamina = 100;
	level = 69;
}

void UserInterface::display() {
	int xscale = 100;
	int yscale = 100;
	update();
	sf::Font font("comicsans.ttf");

	string textHealth = "Hp: " + std::to_string(health);
	string textStamina = "St: " + std::to_string(stamina);
	string textLevel = "Lv: " + std::to_string(level);
	string textWeapon = "Wp: [weapon]";

	sf::Text displayHealth(font, textHealth);
	sf::Text displayStamina(font, textStamina);
	sf::Text displayLevel(font, textStamina);
	sf::Text displayWeapon(font, textWeapon);

	displayHealth.setPosition(sf::Vector2f(-xscale, yscale));
	displayStamina.setPosition(sf::Vector2f(xscale, yscale));
	displayLevel.setPosition(sf::Vector2f(-xscale, -yscale));
	displayWeapon.setPosition(sf::Vector2f(xscale, -yscale));
}