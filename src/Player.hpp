#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Player {
  private:
    sf::Texture texture;

    int x;
    int y;
    int speed;
    
  public:
    Player();

    void update();

    sf::Sprite sprite;
};

#endif
