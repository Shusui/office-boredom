#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Collision.hpp"

class Enemy: public Collision {
  private:
    sf::Texture texture;

    int x;
    int y;
    int speedX;
    int speedY;

  public:
    Enemy(int _x, int _y);

    void update();
    bool checkCollision(sf::FloatRect);

    sf::Sprite sprite;
};

#endif
