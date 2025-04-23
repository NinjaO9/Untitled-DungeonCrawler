#include "Cursor.hpp"

Cursor::Cursor() {

}

Cursor::~Cursor() {

}

void Cursor::update() {
  const sf::Texture texture("Temp.png");
  const sf::Sprite cursor(texture);
  sf::Vector2i mousePos = sf::Mouse::getPosition();
  cursor.setPosition(mousePos);
}
