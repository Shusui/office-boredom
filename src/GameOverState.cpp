#include "GameOverState.hpp"
#include "PlayState.hpp"

GameOverState::GameOverState(Game *_game, int won, int _whichLevel) {
  /*
    won = 0, got caught
    won = 1, didn't finish in time
    won = 2, succesfully finished
   */  
  game = _game;
  whichLevel = _whichLevel;
  
  gameOverText.setFont(game->pixelFont);

  if (won == 0) {
    gameOverText.setCharacterSize(60);
    gameOverText.setPosition(75, 200);

    gameOverText.setString("You're fired!");
  } else if (won == 1) {
    gameOverText.setCharacterSize(60);
    gameOverText.setPosition(90, 200);
    
    gameOverText.setString("You lost!");
  } else if (won == 2) {
    gameOverText.setCharacterSize(60);
    gameOverText.setPosition(90, 200);
    
    gameOverText.setString("You won!");
  }

  pressToPlayText.setFont(game->pixelFont);
  pressToPlayText.setCharacterSize(17);
  pressToPlayText.setPosition(150, 330);
  pressToPlayText.setString("Press Space to start playing");
}

void GameOverState::setup() {

}

void GameOverState::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    game->currentState = new PlayState(game, whichLevel);
  }
}

void GameOverState::draw() {
  game->window.clear();

  game->window.draw(gameOverText);
  game->window.draw(pressToPlayText);

  game->window.display();
}
