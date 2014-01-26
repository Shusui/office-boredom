#include "GameOverState.hpp"
#include "PlayState.hpp"

GameOverState::GameOverState(Game *_game, int won) {
  /*
    won = 0, got caught
    won = 1, didn't finish in time
    won = 2, succesfully finished
   */  
  game = _game;

  gameOverText.setFont(game->arialFont);
  gameOverText.setCharacterSize(70);
  gameOverText.setPosition(130, 200);

  if (won == 0) {
    gameOverText.setString("You're fired!");
  } else if (won == 1) {
    gameOverText.setString("You lost!");
  } else if (won == 2) {
    gameOverText.setString("You won!");
  }

  pressToPlayText.setFont(game->arialFont);
  pressToPlayText.setCharacterSize(30);
  pressToPlayText.setPosition(180, 330);
  pressToPlayText.setString("Press Space to start playing");
}

void GameOverState::setup() {

}

void GameOverState::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    game->currentState = new PlayState(game);
  }
}

void GameOverState::draw() {
  game->window.clear();

  game->window.draw(gameOverText);
  game->window.draw(pressToPlayText);

  game->window.display();
}
