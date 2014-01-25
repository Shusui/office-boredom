#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Collision.hpp"
#include "AStar.hpp"

class PlayState;

class Enemy: public Collision {
  private:
    sf::Texture texture;
    PlayState *state;
    AStar *as;

    float x;
    float y;
    int speedX;
    int speedY;

  public:
    Enemy(PlayState*, float _x, float _y);

    void update();
    bool checkCollision(sf::FloatRect);
    void wallCollision(float,float);
    void pathToTarget();

    sf::Sprite sprite;
};

#endif
