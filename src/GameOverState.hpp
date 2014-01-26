#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "Game.hpp"
#include "State.hpp"

class GameOverState : public State {
  private:
    Game *game;

    sf::Text gameOverText;
    sf::Text pressToPlayText;

    int whichLevel;
    
  public:
    GameOverState(Game *_game, int won, int _whichLevel);

    void setup();
    void update();
    void draw();
};

#endif
