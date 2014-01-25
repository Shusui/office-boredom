#include "GameOverState.hpp"
#include "PlayState.hpp"

GameOverState::GameOverState(Game *_game) {
  game = _game;

  gameOverText.setFont(game->arialFont);
  gameOverText.setCharacterSize(70);
  gameOverText.setPosition(70, 200);
  gameOverText.setString("You're Fired!");
}

void GameOverState::setup() {

}

void GameOverState::update() {

}

void GameOverState::draw() {
  game->window.draw(gameOverText);
}