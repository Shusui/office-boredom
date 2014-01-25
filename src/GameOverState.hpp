#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "Game.hpp"
#include "State.hpp"

class GameOverState : public State {
  private:
    Game *game;

    sf::Text gameOverText;
    
  public:
    GameOverState(Game *_game);

    void setup();
    void update();
    void draw();
};

#endif
