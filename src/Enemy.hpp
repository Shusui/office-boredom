#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <stdio.h>
#include <time.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Collision.hpp"

using namespace std;

class PlayState;
class Game;

class Enemy: public Collision {
  private:
    sf::Texture texture;
    PlayState *state;
    Game *game;

    float x;
    float y;
    float speedX;
    float speedY;
    bool followPlayer;

    sf::Clock searchPlayerClock;
    sf::Clock randomMoveClock;
    vector<sf::Vector2f> path;

  public:
    Enemy(Game*,PlayState*,bool);

    void update();
    bool checkCollision(sf::FloatRect);
    void wallCollision(float,float);
    vector<sf::Vector2f> reconstructPath(vector<int> came_from,vector<sf::Vector2f> set,int idx);
    vector<sf::Vector2f> pathToTarget();

    sf::Sprite sprite;
};

#endif
