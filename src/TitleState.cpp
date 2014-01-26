#include "TitleState.hpp"

TitleState::TitleState(Game *_game) {
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  titleText.setFont(game->pixelFont);
  titleText.setCharacterSize(40);
  titleText.setPosition(50, windowHeight / 2);
  titleText.setString("Bored At The Office");

  pressToPlayText.setFont(game->pixelFont);
  pressToPlayText.setCharacterSize(17);
  pressToPlayText.setPosition(150, 330);
  pressToPlayText.setString("Press Space to start playing");
}

void TitleState::setup() {

}

void TitleState::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    game->currentState = new PlayState(game);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    game->currentState = new MapEditor(game, 1);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    game->window.close();
  }
}

void TitleState::draw() {
  game->window.clear();

  game->window.draw(titleText);
  game->window.draw(pressToPlayText);
  
  game->window.display();
}
