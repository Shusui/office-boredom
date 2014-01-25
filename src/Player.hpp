#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Collision.hpp"

class Player: public Collision {
  private:
    sf::Texture texture;

    int x;
    int y;
    int speed;

    sf::SoundBuffer buffer;
    sf::Sound satisfactionSound;

  public:
    Player();

    void update();
    bool checkCollision(sf::FloatRect);

    sf::Sprite sprite;

    int satisfaction;
    sf::RectangleShape satisfactionOutline;
    sf::RectangleShape satisfactionFill;
};

#endif
