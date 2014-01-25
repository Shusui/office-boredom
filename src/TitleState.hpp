#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "Game.hpp"
#include "State.hpp"
#include "PlayState.hpp"

class TitleState : public State {
  private:
    Game *game;

    int windowWidth;
    int windowHeight;
    
    sf::Text titleText;
    sf::Text pressToPlayText;
    
  public:
    TitleState(Game *_game);
    
    void setup();
    void update();
    void draw();
};

#endif
