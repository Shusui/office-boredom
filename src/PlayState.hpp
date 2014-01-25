#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <stdio.h>
#include <sstream>
#include <string>
#include <cmath>

#include "Game.hpp"
#include "State.hpp"

class PlayState : public State
{
  private:
    Game *game;

    sf::Text fps;

    int windowWidth;
    int windowHeight;

  public:
    PlayState(Game *_game);

    void setup();
    void update();
    void draw();
};

#endif