#include "Player.hpp"
#include "PlayState.hpp"
#include "Tile.hpp"

#include <math.h>

Player::Player(Game *_game, PlayState *_state) {
  game = _game;
  state = _state;
  x = 0;
  y = 0;
  speed = 2;

  buffer.loadFromFile("res/satisfaction_sound.wav");
  satisfactionSound.setBuffer(buffer);
  satisfactionSound.setLoop(true);

  texture = game->myTextureFactory.findTexture("player");
  sprite.setTexture(*texture);
  sprite.scale(0.70, 0.70);

  do {
    x = (int)(rand() % state->tilemap->width);
    y = (int)(rand() % state->tilemap->height);
  } while (state->tilemap->rawMap[(int) y][(int) x]->type != GROUND);

  x = x * state->tilemap->tileSize;
  y = y * state->tilemap->tileSize;
  sprite.setPosition(x, y);

  satisfaction = 0;
  satisfactionOutline.setPosition(5, 5);
  satisfactionOutline.setSize(sf::Vector2f(200, 30));
  satisfactionOutline.setOutlineThickness(2);
  satisfactionOutline.setOutlineColor(sf::Color(255, 0, 0, 50));
  satisfactionOutline.setFillColor(sf::Color(0, 0, 0, 70));
  satisfactionFill.setPosition(5, 5);
  satisfactionFill.setFillColor(sf::Color(255, 0, 0, 30));
}

Player::~Player() {
  buffer.~SoundBuffer();
  satisfactionSound.~Sound();
}

void Player::update() {
  float oldX = x;
  float oldY = y;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    x -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    x += speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    y -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    y += speed;
  }

  wallCollision(oldX, oldY);
  sprite.setPosition(x, y);

  if (x != oldX || y != oldY) return;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    isSatisfying = true;
    satisfaction++;

    if (satisfactionSound.getStatus() != sf::Sound::Playing) {
      satisfactionSound.play();
    }
  } else {
    satisfactionSound.stop();
    isSatisfying = false;
  }

  /* Handle satisfaction */
  satisfactionFill.setSize(sf::Vector2f(satisfaction, 30));

  if (satisfaction == 200) {
    game->currentState = new GameOverState(game, 2);
    satisfactionSound.stop();
  }
}

bool Player::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}

void Player::wallCollision(float oldX, float oldY) {
  sprite.setPosition(x, oldY);

  for (int ty = 0; ty < state->tilemap->height; ty++){
    for (int tx = 0; tx < state->tilemap->width; tx++){
      if(state->tilemap->rawMap[ty][tx]->type == WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())) {
        if (x > oldX) {
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x - sprite.getLocalBounds().width * sprite.getScale().x;
        } else if (x < oldX) {
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x + state->tilemap->tileSize;
        } else {
          x = oldX;
        }

        break;
      }
    }
  }

  sprite.setPosition(oldX, y);

  for (int ty = 0; ty < state->tilemap->height; ty++){
    for (int tx = 0; tx < state->tilemap->width; tx++){
      if (state->tilemap->rawMap[ty][tx]->type == WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())){
        if (y > oldY){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y - sprite.getLocalBounds().height * sprite.getScale().y;
        } else if (y < oldY){
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y + state->tilemap->tileSize;
        } else {
          y = oldY;
        }

        break;
      }
    }
  }

  sprite.setPosition(x, y);

  for (int ty = 0;ty < state->tilemap->height; ty++){
    for (int tx = 0;tx < state->tilemap->width; tx++){
      if (state->tilemap->rawMap[ty][tx]->type == WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())){
        if (x > oldX){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x - sprite.getLocalBounds().width * sprite.getScale().x;
        } else if (x<oldX){
          x = state->tilemap->rawMap[ty][tx]->sprite.getPosition().x + state->tilemap->tileSize;
        } else {
          x = oldX;
        }

        if (y > oldY) {
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y - sprite.getLocalBounds().height * sprite.getScale().y;
        } else if (y < oldY) {
          y = state->tilemap->rawMap[ty][tx]->sprite.getPosition().y + state->tilemap->tileSize;
        } else {
          y = oldY;
        }

        break;
      }
    }
  }
}
