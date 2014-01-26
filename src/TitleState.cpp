#include "TitleState.hpp"

TitleState::TitleState(Game *_game) {
  game = _game;
  windowWidth = game->window.getSize().x;
  windowHeight = game->window.getSize().y;

  titleText.setFont(game->arialFont);
  titleText.setCharacterSize(72);
  titleText.setPosition(70, windowHeight / 2);
  titleText.setString("Office Boredom");

  pressToPlayText.setFont(game->arialFont);
  pressToPlayText.setCharacterSize(30);
  pressToPlayText.setPosition(180, 330);
  pressToPlayText.setString("Press Space to start playing");
}

void TitleState::setup() {

}

void TitleState::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    game->currentState = new PlayState(game);
  }
}

void TitleState::draw() {
  game->window.clear();

  game->window.draw(titleText);
  game->window.draw(pressToPlayText);
  
  game->window.display();
}
