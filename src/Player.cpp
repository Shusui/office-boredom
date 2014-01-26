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

  texture = game->myTextureFactory.findTexture("player_sprites");
  sprite.setTexture(*texture);
  sprite.scale(0.9,0.9);
  spriteSource = sf::Vector2f(0,0);
  spriteSize = sf::Vector2i(32,32);
  sprite.setTextureRect(sf::IntRect((int)floor(spriteSource.x)*spriteSize.x,spriteSource.y*spriteSize.y,spriteSize.x,spriteSize.y));
  do {
    x = (int)(rand() % state->tilemap->width);
    y = (int)(rand() % state->tilemap->height);
  } while (state->tilemap->rawMap[(int) y][(int) x]->type != GROUND);

  x = x * state->tilemap->tileSize;
  y = y * state->tilemap->tileSize;
  sprite.setPosition(x, y);

  satisfaction = 0;
  maxSatisfaction = state->windowWidth;
  satisfactionFill.setPosition(0, state->windowHeight - 5);
  satisfactionFill.setFillColor(sf::Color(255, 0, 0));
}

Player::~Player() {
  buffer.~SoundBuffer();
  satisfactionSound.~Sound();
}

void Player::update() {
  float oldX = x;
  float oldY = y;
  bool moved = false;
  bool movedLeft = false;
  bool movedRight = false;
  bool movedTop = false;
  bool movedBot = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    moved = true;
    movedLeft = true;
    spriteSource.y=3;
    x -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    moved = true;
    movedRight = true;
    spriteSource.y=2;
    x += speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    moved = true;
    movedTop = true;
    spriteSource.y=1;
    y -= speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    moved = true;
    movedBot = true;
    spriteSource.y=0;
    y += speed;
  }

  if(moved==true){
    spriteSource.x+=0.2;
    if(spriteSource.x >= (int)texture->getSize().x/spriteSize.x){
      spriteSource.x = 0;
    }
  }

  if((movedLeft || movedRight) && (movedTop || movedBot) && (!movedLeft || !movedRight) && (!movedTop || !movedBot)){
    y = oldY;
    x = oldX;

    if(movedLeft)
      x -= speed*cos(3.14/4);
    else if(movedRight)
      x += speed*cos(3.14/4);

    if(movedTop)
      y -= speed*sin(3.14/4);
    else if(movedBot)
      y += speed*sin(3.14/4);
  }

  wallCollision(oldX, oldY);
  sprite.setTextureRect(sf::IntRect((int)floor(spriteSource.x)*spriteSize.x,spriteSource.y*spriteSize.y,spriteSize.x,spriteSize.y));
  sprite.setPosition(x, y);

  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F) || moved) {
    satisfactionSound.stop();
    isSatisfying = false;
    satisfaction -= 0.25;
    if (satisfaction <0) satisfaction=0;
    satisfactionFill.setSize(sf::Vector2f(satisfaction, 5));
    return;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
    if (state->hasBegun) {
      isSatisfying = true;
      satisfaction += 2;

      if (satisfactionSound.getStatus() != sf::Sound::Playing) {
	      satisfactionSound.play();
      }
    }
  }
  /* Handle satisfaction */
  satisfactionFill.setSize(sf::Vector2f(satisfaction, 5));

  if (satisfaction >= maxSatisfaction) {
    sf::Time delayTime = sf::seconds(0.5f);
    sf::sleep(delayTime);

    state->currentLevel++;
    state->enemies.clear();
    state->setup();
    satisfactionSound.stop();
  }
}

bool Player::checkCollision(sf::FloatRect other) {
  return sprite.getGlobalBounds().intersects(other);
}

void Player::wallCollision(float oldX, float oldY) {
  sprite.setPosition(x, oldY);

  for (int ty = 0; ty < state->tilemap->height; ty++) {
    for (int tx = 0; tx < state->tilemap->width; tx++) {
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

  for (int ty = 0; ty < state->tilemap->height; ty++) {
    for (int tx = 0; tx < state->tilemap->width; tx++) {
      if (state->tilemap->rawMap[ty][tx]->type == WALL &&
         this->checkCollision(state->tilemap->rawMap[ty][tx]->sprite.getGlobalBounds())) {
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

  sprite.setPosition(x, y);

  for (int ty = 0;ty < state->tilemap->height; ty++) {
    for (int tx = 0;tx < state->tilemap->width; tx++) {
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
