#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "TextureManager.hpp"

class Ui {
  private:
    /*int health;
    int stamina;
    int level;
    Player *selectedPlayer;
    Weapon *selectedWeapon;*/

  public:
    Ui();
    ~Ui();
    void update();
    void display();
};
