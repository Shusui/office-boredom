#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <stdio.h>
#include <sstream>
#include <string>
#include <cmath>
#include <time.h>

#include "Game.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Tilemap.hpp"

class PlayState : public State {
  private:
    Game *game;

    std::string gameClockString;
    sf::Text gameClockText;

    sf::Clock gameClock;
    
  public:    
    PlayState(Game *_game);

    void setup();
    void update();
    void draw();

    Tilemap *tilemap;
    Player *player;
    std::vector<Enemy*> enemies;
    int maxEnemies;

    int windowWidth;
    int windowHeight;
};

#endif
