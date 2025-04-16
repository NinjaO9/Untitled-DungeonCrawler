#include "Ui.hpp"

Ui::Ui() {

};

Ui::~Ui() {

};

void Ui::update() {
	//health = selectedPlayer->hp;
	//stamina = selectedPlayer->stamina;
	//level = selectedPlayer->level;
	//weponEquip = selectedPlayer->weapon;

	health = 100;
	stamina = 100;
	level = 69;
};

void display() {
	int scale = 100;
	update();
	sf::Font font("comicsans.ttf");
	sf::Text displayHealth(font, "Hp: " + health);
	sf::Text displayStamina(font, "St: " + stamina);
	sf::Text displayLevel(font, "Lv: " + level);

	displayHealth.setposition(scale, scale);
	displayStamina.setposition(-scale, scale);
	displayLevel.setposition(-scale, -scale);
};
