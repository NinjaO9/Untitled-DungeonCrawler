#include "Entity.hpp"
//#include "Player.hpp" // uncomment once player class exists
#include <string>
using std::string;

class Ui {
  private:
    int health;
    int stamina;
    int level;
    string *weponEquip;
    //Player *selectedPlayer; // unvomment once player class exits
  public:
    Ui();
    ~Ui();
    void update();
    void display();
};
