#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "Collision.hpp"
#include "GameOverState.hpp"

/*Forward declaration so that PlayState *state can exist
  
  We don't need to include header because it's only a pointer and
  including the header would create an error of mutually depentend
  classes
*/
class PlayState;

class Player: public Collision {
  private:
    Game *game;
    PlayState *state;

    float x;
    float y;
    float speed;

    sf::SoundBuffer buffer;
    sf::Sound satisfactionSound;

  public:
    Player(Game *_game, PlayState *_state);
    ~Player();

    void update();
    bool checkCollision(sf::FloatRect);
    void wallCollision(float,float);

    sf::Texture *texture;
    sf::Sprite sprite;

    int satisfaction;
    bool isSatisfying;
    sf::RectangleShape satisfactionOutline;
    int maxSatisfaction;
    sf::RectangleShape satisfactionFill;
};

#endif
