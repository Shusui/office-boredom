#include "Enemy.hpp"


Enemy::Enemy(int _x, int _y) {
  x = _x;
  y = _y;
  srand(time(NULL));
  speedX = rand() % 4 + 1;
  speedY = rand() % 5 + 1;

  texture.loadFromFile("res/enemy.png");
  sprite.setTexture(texture);
}

void Enemy::update() {
  x += speedX;
  y += speedY;

  if (x < 0) {
    x = 0;
    speedX *= (-1);
  } else if (x > 608) {
    x = 608;
    speedX *= (-1);
  }

  if (y < 0) {
    y = 0;
    speedY *= (-1);
  } else if (y > 448) {
    y = 448;
    speedY *= (-1);
  }

  sprite.setPosition(x, y);
}

bool Enemy::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}
