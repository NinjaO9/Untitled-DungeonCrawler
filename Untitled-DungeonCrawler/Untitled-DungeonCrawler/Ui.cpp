#include "Ui.hpp"

/*Ui::Ui(Player *newPlayer) {
	selectedPlayer = newPlayer;
};*/

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
	int xscale = 100;
  int yscale = 100;
	update();
  int healthBar = health / 10;
  int staminaBar = stamina / 10;
	sf::Font font("comicsans.ttf");
  string screenHealth = "Hp: [";
  string screenStamina = "St: [";
  string screenLevel = "Lv: " + level;
  for (int i = 0; i < healthBar; i++) {
    screenHealth += "#";
  }
  for (int i = 0; i < staminaBar; i++) {
    screenStamina += "#";
  }
	sf Text::displayHealth(font, screenHealth);
	sf::Text displayStamina(font, screenStamina);
	sf::Text displayLevel(font, screenLevel);

	displayHealth.setposition(xscale, yscale);
	displayStamina.setposition(-xscale, yscale);
	displayLevel.setposition(-xscale, -yscale);
};
