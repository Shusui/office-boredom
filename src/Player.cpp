#include "Player.hpp"

Player::Player() {
  x = 0;
  y = 0;
  speed = 3;

  buffer.loadFromFile("res/satisfactionSound.wav");
  satisfactionSound.setBuffer(buffer);
  satisfactionSound.setLoop(true);

  texture.loadFromFile("res/player.png");
  sprite.setTexture(texture);

  satisfaction = 0;
  satisfactionOutline.setPosition(5, 5);
  satisfactionOutline.setSize(sf::Vector2f(200, 30));
  satisfactionOutline.setOutlineThickness(2);
  satisfactionOutline.setOutlineColor(sf::Color(255, 0, 0, 50));
  satisfactionOutline.setFillColor(sf::Color(0, 0, 0, 70));
  satisfactionFill.setPosition(5, 5);
  satisfactionFill.setFillColor(sf::Color(255, 0, 0, 30));
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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    satisfaction++;

    if (satisfactionSound.getStatus() != sf::Sound::Playing) {
      satisfactionSound.play();
    }
  } else {
    satisfactionSound.stop();
  }

  /* Handle satisfaction */
  satisfactionFill.setSize(sf::Vector2f(satisfaction, 30));

  sprite.setPosition(x, y);
}

bool Player::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}
