#include "Player.hpp"

Player::Player() {
  x = 0;
  y = 0;
  speed = 3;

  texture.loadFromFile("res/player.png");
  sprite.setTexture(texture);
}

void Player::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    x -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    x += speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    y -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    y += speed;
  }

  sprite.setPosition(x, y);
}

bool Player::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}
